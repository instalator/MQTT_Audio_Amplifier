#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 

char b[2];
byte mac[]    = { 0x0A, 0x2F, 0x30, 0x42, 0x39, 0x1F };
byte server[] = { 192, 168, 1, 190 }; //IP Брокера
byte ip[]     = { 192, 168, 1, 153 }; //IP Клиента (Arduino)
////////////////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String strTopic = String(topic);
    String strPayload = String((char*)payload);
    callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);
#define id_connect "myhome-Audio_Amplifier"

#define PIN_AMP_1 17
#define PIN_AMP_2 16
#define PIN_AMP_3 15
#define PIN_AMP_4 14
#define PIN_AMP_5 20

#define PIN_VOL_1 5
#define PIN_VOL_2 3
#define PIN_VOL_3 9
#define PIN_VOL_4 6
#define PIN_VOL_5 10

#define PIN_SHTD 2
#define PIN_FADE 4

///////////////Объявляем порты ввода-вывода
const int start_DI_pin []= {0}; // Порты Ввода
int n_DI_pin = sizeof(start_DI_pin) / sizeof(start_DI_pin[0])-1; //Вычисляем длинну массива

const int start_DO_pin []= {PIN_AMP_1, PIN_AMP_2, PIN_AMP_3, PIN_AMP_4, PIN_AMP_5, PIN_VOL_1, PIN_VOL_2, PIN_VOL_3, PIN_VOL_4, PIN_VOL_5, PIN_SHTD, PIN_FADE}; //Порты Вывода
int n_DO_pin = sizeof(start_DO_pin) / sizeof(start_DO_pin[0])-1; //Вычисляем длинну массива

void PubTopic (){
    client.publish("myhome/Audio_Amplifier/zone_1", "false");
    client.publish("myhome/Audio_Amplifier/zone_2", "false");
    client.publish("myhome/Audio_Amplifier/zone_3", "false");
    client.publish("myhome/Audio_Amplifier/zone_4", "false");
    client.publish("myhome/Audio_Amplifier/zone_5", "false");
    client.publish("myhome/Audio_Amplifier/vol_1", "10");
    client.publish("myhome/Audio_Amplifier/vol_2", "10");
    client.publish("myhome/Audio_Amplifier/vol_3", "10");
    client.publish("myhome/Audio_Amplifier/vol_4", "10");
    client.publish("myhome/Audio_Amplifier/vol_5", "10");
    client.publish("myhome/Audio_Amplifier/fade", "false");
    client.publish("myhome/Audio_Amplifier/shtd", "false");
  }
////////////////////////////////////////////////////////////////////////////
void setup() {
    //Объявляем порты Digital inputs/outputs
  for(int i=0 ;i<=n_DI_pin; i++) { pinMode (start_DI_pin [i], INPUT); }
  for(int i=0 ;i<=n_DO_pin; i++) { pinMode (start_DO_pin [i], OUTPUT); }

  Ethernet.begin(mac, ip);
  if (client.connect(id_connect)) {
    PubTopic();
    client.subscribe("myhome/Audio_Amplifier/#");
  }
}
/////////////////////////////////////////////////////////////////////////
void loop() {
  client.loop();

  if (!client.connected() && (millis() - previousMillis > 10000)) {
    previousMillis = millis();
    if (client.connect(id_connect)) {
      PubTopic();
      client.subscribe("myhome/Audio_Amplifier/#");
    }
  }
}
