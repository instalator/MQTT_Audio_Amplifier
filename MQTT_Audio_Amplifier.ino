#include <EEPROM.h>
#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 

//#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 8
//#define ETHERNET_SHIELD_SPI_CS 8

char b[2];
byte mac[]    = { 0x0A, 0x2F, 0x30, 0x42, 0x39, 0x1F };
byte server[] = { 192, 168, 1, 190 }; //IP Брокера
byte ip[]     = { 192, 168, 1, 153 }; //IP Клиента (Arduino)

byte vol_1,vol_2,vol_3,vol_4,vol_5,shtd,fade;

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
long previousMillis = 0;

#define PIN_AMP_1 17
#define PIN_AMP_2 16
#define PIN_AMP_3 15
#define PIN_AMP_4 14
#define PIN_AMP_5 7

#define PIN_VOL_1 5
#define PIN_VOL_2 3
#define PIN_VOL_3 9
#define PIN_VOL_4 6
#define PIN_VOL_5 10

#define PIN_SHTD 4
#define PIN_FADE 2

void PubTopic () {
  client.publish("myhome/Audio_Amplifier/save", "false");
  client.publish("myhome/Audio_Amplifier/zone_1", "false");
  client.publish("myhome/Audio_Amplifier/zone_2", "false");
  client.publish("myhome/Audio_Amplifier/zone_3", "false");
  client.publish("myhome/Audio_Amplifier/zone_4", "false");
  client.publish("myhome/Audio_Amplifier/zone_5", "false");
  client.publish("myhome/Audio_Amplifier/vol_1", IntToChar(vol_1));
  client.publish("myhome/Audio_Amplifier/vol_2", IntToChar(vol_2));
  client.publish("myhome/Audio_Amplifier/vol_3", IntToChar(vol_3));
  client.publish("myhome/Audio_Amplifier/vol_4", IntToChar(vol_4));
  client.publish("myhome/Audio_Amplifier/vol_5", IntToChar(vol_5));
  client.publish("myhome/Audio_Amplifier/fade", IntToBool(fade));
  client.publish("myhome/Audio_Amplifier/shtd", IntToBool(shtd));
  client.publish("myhome/Audio_Amplifier/connection", "true");
}
////////////////////////////////////////////////////////////////////////////
void setup() {
   vol_1 = EEPROM.read(1);
   vol_2 = EEPROM.read(2);
   vol_3 = EEPROM.read(3);
   vol_4 = EEPROM.read(4);
   vol_5 = EEPROM.read(5);
   shtd = EEPROM.read(6);
   fade = EEPROM.read(7);
  if (vol_1 == 255 && vol_2 == 255 && vol_3 == 255 && vol_4 == 255 && vol_5 == 255 && shtd == 255 && fade == 255) {
    vol_1 = 30;
    vol_2 = 30;
    vol_3 = 30;
    vol_4 = 30;
    vol_5 = 30;
    shtd = 0;
    fade = 1;
  } else {
    if (shtd > 0){shtd = 1;}
    if (fade > 0){fade = 1;}
  }
DDRD |= B11111100;
DDRB |= B00000110;
DDRC |= B00001111;
  //PORTB |= B1100;
  digitalWrite(PIN_AMP_1, HIGH);
  digitalWrite(PIN_AMP_2, HIGH);
  digitalWrite(PIN_AMP_3, HIGH);
  digitalWrite(PIN_AMP_4, HIGH);
  digitalWrite(PIN_AMP_5, HIGH);
  analogWrite(PIN_VOL_1, vol_1);
  analogWrite(PIN_VOL_2, vol_2);
  analogWrite(PIN_VOL_3, vol_3);
  analogWrite(PIN_VOL_4, vol_4);
  analogWrite(PIN_VOL_5, vol_5);
  digitalWrite(PIN_SHTD, shtd);
  digitalWrite(PIN_FADE, fade);
  
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
