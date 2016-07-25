//--------------------------------- Functions ---------------------------------//
char* ToChar (String intstr){
    intstr.toCharArray(b, 2);
    return b;
  }
String InvertOut(int pin){
    delay(pause);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    out = String(digitalRead(pin), DEC);
    return out;
}
 
void callback_iobroker(String strTopic, String strPayload) {
  if (strTopic == "myhome/Audio_Amplifier/zone_1") {
        if (strPayload == "true") {
            digitalWrite(PIN_AMP_1, true);
            client.publish("myhome/Audio_Amplifier/zone_1", "true");
        } else {
            digitalWrite(PIN_AMP_1, false);
            client.publish("myhome/Audio_Amplifier/zone_1", "false");
        }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_2") {
        if (strPayload == "true") {
            digitalWrite(PIN_AMP_2, true);
            client.publish("myhome/Audio_Amplifier/zone_2", "true");
        } else {
            digitalWrite(PIN_AMP_2, false);
            client.publish("myhome/Audio_Amplifier/zone_2", "false");
        }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_3") {
        if (strPayload == "true") {
            digitalWrite(PIN_AMP_3, true);
            client.publish("myhome/Audio_Amplifier/zone_3", "true");
        } else {
            digitalWrite(PIN_AMP_3, false);
            client.publish("myhome/Audio_Amplifier/zone_3", "false");
        }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_4") {
        if (strPayload == "true") {
            digitalWrite(PIN_AMP_4, true);
            client.publish("myhome/Audio_Amplifier/zone_4", "true");
        } else {
            digitalWrite(PIN_AMP_4, false);
            client.publish("myhome/Audio_Amplifier/zone_4", "false");
        }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_5") {
        if (strPayload == "true") {
            digitalWrite(PIN_AMP_5, true);
            client.publish("myhome/Audio_Amplifier/zone_5", "true");
        } else {
            digitalWrite(PIN_AMP_5, false);
            client.publish("myhome/Audio_Amplifier/zone_5", "false");
        }
  }
  /////////////////////////////////////////////////////////
  if (strTopic == "myhome/Audio_Amplifier/vol_1") {
    //if (strPayload == "true") {
        analogWrite(PIN_VOL_1, strPayload);
        client.publish("myhome/Audio_Amplifier/vol_1", "true");
    //}
  }
      
  }
