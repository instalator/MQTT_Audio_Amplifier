#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT  
#include <avr/wdt.h>
#include <TextFinder.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

//#define ETHERNET_SHIELD_SPI_CS 8
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

#define ID_CONNECT "Audio_Amplifier"

#define ADDR_MQTTIP  200 // ячейка хранения настроект mqtt сервера
#define ADDR_MAC     210 // ячейка хранения настроект MAC
#define ADDR_IDCHEK  199 // ячейка хранения флага сохранены IP и MAC в еепром или нет


const char htmlx0[] PROGMEM = "<html><title>Controller IO setup Page</title><body marginwidth=\"0\" marginheight=\"0\" ";
const char htmlx1[] PROGMEM = "leftmargin=\"0\" \"><table bgcolor=\"#999999\" border";
const char htmlx2[] PROGMEM = "=\"0\" width=\"100%\" cellpadding=\"1\" ";
const char htmlx3[] PROGMEM = "\"><tr><td>&nbsp Controller IO setup Page</td></tr></table><br>";
const char* const string_table0[] PROGMEM = {htmlx0, htmlx1, htmlx2, htmlx3};

const char htmla0[] PROGMEM = "<script>function hex2num (s_hex) {eval(\"var n_num=0X\" + s_hex);return n_num;}";
const char htmla1[] PROGMEM = "</script><table><form><input type=\"hidden\" name=\"SBM\" value=\"1\"><tr><td>MAC:&nbsp&nbsp&nbsp";
const char htmla2[] PROGMEM = "<input id=\"T1\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT1\" value=\"";
const char htmla3[] PROGMEM = "\">.<input id=\"T3\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT2\" value=\"";
const char htmla4[] PROGMEM = "\">.<input id=\"T5\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT3\" value=\"";
const char htmla5[] PROGMEM = "\">.<input id=\"T7\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT4\" value=\"";
const char htmla6[] PROGMEM = "\">.<input id=\"T9\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT5\" value=\"";
const char htmla7[] PROGMEM = "\">.<input id=\"T11\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT6\" value=\"";
const char* const string_table1[] PROGMEM = {htmla0, htmla1, htmla2, htmla3, htmla4, htmla5, htmla6, htmla7};

const char htmlb0[] PROGMEM = "\"><input id=\"T2\" type=\"hidden\" name=\"DT1\"><input id=\"T4\" type=\"hidden\" name=\"DT2";
const char htmlb1[] PROGMEM = "\"><input id=\"T6\" type=\"hidden\" name=\"DT3\"><input id=\"T8\" type=\"hidden\" name=\"DT4";
const char htmlb2[] PROGMEM = "\"><input id=\"T10\" type=\"hidden\" name=\"DT5\"><input id=\"T12\" type=\"hidden\" name=\"D";
const char htmlb3[] PROGMEM = "T6\"></td></tr><tr><td>MQTT: <input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT7\" value=\"";
const char htmlb4[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT8\" value=\"";
const char htmlb5[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT9\" value=\"";
const char htmlb6[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT10\" value=\"";
const char* const string_table2[] PROGMEM = {htmlb0, htmlb1, htmlb2, htmlb3, htmlb4, htmlb5, htmlb6};

const char htmlc0[] PROGMEM = "\"></td></tr><tr><td><br></td></tr><tr><td><input id=\"button1\"type=\"submit\" value=\"SAVE\" ";
const char htmlc1[] PROGMEM = "></td></tr></form></table></body></html>";
const char* const string_table3[] PROGMEM = {htmlc0, htmlc1};

const char htmld0[] PROGMEM = "Onclick=\"document.getElementById('T2').value ";
const char htmld1[] PROGMEM = "= hex2num(document.getElementById('T1').value);";
const char htmld2[] PROGMEM = "document.getElementById('T4').value = hex2num(document.getElementById('T3').value);";
const char htmld3[] PROGMEM = "document.getElementById('T6').value = hex2num(document.getElementById('T5').value);";
const char htmld4[] PROGMEM = "document.getElementById('T8').value = hex2num(document.getElementById('T7').value);";
const char htmld5[] PROGMEM = "document.getElementById('T10').value = hex2num(document.getElementById('T9').value);";
const char htmld6[] PROGMEM = "document.getElementById('T12').value = hex2num(document.getElementById('T11').value);\"";
const char* const string_table4[] PROGMEM = {htmld0, htmld1, htmld2, htmld3, htmld4, htmld5, htmld6};

char b[2];
byte mac[]    = { 0x6A, 0x2F, 0x38, 0x42, 0x33, 0x1F }; //MAC адрес контроллера
byte mqtt_serv[] = {192, 168, 88, 190}; //IP MQTT брокера

byte vol_1, vol_2, vol_3, vol_4, vol_5, shtd, fade;
long previousMillis = 0;
int count = 0;
const byte ID = 0x91;
char buffer[100];

////////////////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
EthernetServer http_server(80);
PubSubClient mqtt(ethClient);

////////////////////////////////////////////////////////////////////////////
void setup() {
  MCUSR = 0;
  wdt_disable();
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
    if (shtd > 0) {
      shtd = 1;
    }
    if (fade > 0) {
      fade = 1;
    }
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
  delay(1000);
  httpSetup();
  mqttSetup();
  delay(1000);
  if (mqtt.connect(ID_CONNECT)) {
    PubTopic();
    mqtt.subscribe("myhome/Audio_Amplifier/#");
  }
  wdt_enable(WDTO_8S);
}

void reconnect() {
  count++;
  wdt_reset();
  if (mqtt.connect(ID_CONNECT)) {
    count = 0;
    wdt_reset();
    mqtt.publish("myhome/Audio_Amplifier/connection", "true");
    PubTopic();
    mqtt.subscribe("myhome/Audio_Amplifier/#");
  }
  if (count > 50) {
    wdt_enable(WDTO_15MS);
    for (;;) {}
  }
}
/////////////////////////////////////////////////////////////////////////

void loop() {
  wdt_reset();
  checkHttp();
  mqtt.loop();
  if (!mqtt.connected() && (millis() - previousMillis > 10000)) {
    previousMillis = millis();
    if (Ethernet.begin(mac) == 0) {
        Reset();
      } else {
        reconnect();
      }
  }
}

void PubTopic () {
  char s[16];
  sprintf(s, "%d.%d.%d.%d", Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
  mqtt.publish("myhome/Audio_Amplifier/ip", s);
  mqtt.publish("myhome/Audio_Amplifier/save", "false");
  mqtt.publish("myhome/Audio_Amplifier/zone_1", "false");
  mqtt.publish("myhome/Audio_Amplifier/zone_2", "false");
  mqtt.publish("myhome/Audio_Amplifier/zone_3", "false");
  mqtt.publish("myhome/Audio_Amplifier/zone_4", "false");
  mqtt.publish("myhome/Audio_Amplifier/zone_5", "false");
  mqtt.publish("myhome/Audio_Amplifier/vol_1", IntToChar(vol_1));
  mqtt.publish("myhome/Audio_Amplifier/vol_2", IntToChar(vol_2));
  mqtt.publish("myhome/Audio_Amplifier/vol_3", IntToChar(vol_3));
  mqtt.publish("myhome/Audio_Amplifier/vol_4", IntToChar(vol_4));
  mqtt.publish("myhome/Audio_Amplifier/vol_5", IntToChar(vol_5));
  mqtt.publish("myhome/Audio_Amplifier/fade", IntToBool(fade));
  mqtt.publish("myhome/Audio_Amplifier/shtd", IntToBool(shtd));
  mqtt.publish("myhome/Audio_Amplifier/connection", "true");
}

void mqttSetup() {
  int idcheck = EEPROM.read(ADDR_IDCHEK);
  if (idcheck == ID) {
    for (int i = 0; i < 4; i++) {
      mqtt_serv[i] = EEPROM.read(i + ADDR_MQTTIP);
    }
  }
  mqtt.setServer(mqtt_serv, 1883);
  mqtt.setCallback(callback);
}

void httpSetup() {
  int idcheck = EEPROM.read(ADDR_IDCHEK);
  if (idcheck == ID) {
    for (int i = 0; i < 6; i++) {
      mac[i] = EEPROM.read(i + ADDR_MAC);
    }
  }
  Ethernet.begin(mac);
}

void checkHttp() {
  EthernetClient http = http_server.available();
  if (http) {
    TextFinder  finder(http );
    while (http.connected()) {
      if (http.available()) {
        if ( finder.find("GET /") ) {
          if (finder.findUntil("setup", "\n\r")) {
            if (finder.findUntil("SBM", "\n\r")) {
              byte SET = finder.getValue();
              while (finder.findUntil("DT", "\n\r")) {
                int val = finder.getValue();
                if (val >= 1 && val <= 6) {
                  mac[val - 1] = finder.getValue();
                }
                if (val >= 7 && val <= 10) {
                  mqtt_serv[val - 7] = finder.getValue();
                }
              }
              for (int i = 0 ; i < 6; i++) {
                EEPROM.write(i + ADDR_MAC, mac[i]);
              }
              for (int i = 0 ; i < 4; i++) {
                EEPROM.write(i + ADDR_MQTTIP, mqtt_serv[i]);
              }
              EEPROM.write(ADDR_IDCHEK, ID);
              http.println("HTTP/1.1 200 OK");
              http.println("Content-Type: text/html");
              http.println();
              for (int i = 0; i < 4; i++) {
                strcpy_P(buffer, (char*)pgm_read_word(&(string_table0[i])));
                http.print( buffer );
              }
              http.println();
              http.print("Saved!");
              http.println();
              http.print("Restart");
              for (int i = 1; i < 10; i++) {
                http.print(".");
                delay(500);
              }
              http.println("OK");
              Reset(); // ребутим с новыми параметрами
            }
            http.println("HTTP/1.1 200 OK");
            http.println("Content-Type: text/html");
            http.println();
            for (int i = 0; i < 4; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table0[i])));
              http.print( buffer );
            }
            for (int i = 0; i < 3; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[i])));
              http.print( buffer );
            }
            http.print(mac[0], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[3])));
            http.print( buffer );
            http.print(mac[1], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[4])));
            http.print( buffer );
            http.print(mac[2], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[5])));
            http.print( buffer );
            http.print(mac[3], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[6])));
            http.print( buffer );
            http.print(mac[4], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[7])));
            http.print( buffer );
            http.print(mac[5], HEX);
            for (int i = 0; i < 4; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[i])));
              http.print( buffer );
            }
            http.print(mqtt_serv[0], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[4])));
            http.print( buffer );
            http.print(mqtt_serv[1], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[5])));
            http.print( buffer );
            http.print(mqtt_serv[2], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[6])));
            http.print( buffer );
            http.print(mqtt_serv[3], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table3[0])));
            http.print( buffer );
            for (int i = 0; i < 7; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table4[i])));
              http.print( buffer );
            }
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table3[1])));
            http.print( buffer );
            break;
          }
        }
        http.println("HTTP/1.1 200 OK");
        http.println("Content-Type: text/html");
        http.println();
        http.print("IOT controller [");
        http.print(ID_CONNECT);
        http.print("]: go to <a href=\"/setup\"> setup</a>");
        break;
      }
    }
    delay(1);
    http.stop();
  } else {
    return;
  }
}

void Reset() {
  for (;;) {}
}
