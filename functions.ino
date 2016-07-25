//--------------------------------- Functions ---------------------------------//
char* ToChar (String intstr) {
  intstr.toCharArray(b, 4);
  return b;
}
char* IntToChar (int intV) {
  String stringVar = String(intV, DEC);
  stringVar.toCharArray(b, 4);
  return b;
}
void Save(){
    EEPROM.write(1, byte(vol_1));
    EEPROM.write(2, byte(vol_2));
    EEPROM.write(3, byte(vol_3));
    EEPROM.write(4, byte(vol_4));
    EEPROM.write(5, byte(vol_5));
    EEPROM.write(6, byte(shtd));
    EEPROM.write(7, byte(fade));
}
/*
  String InvertOut(int pin){
    //delay(pause);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    out = String(digitalRead(pin), DEC);
    return out;
  }
*/

void callback_iobroker(String strTopic, String strPayload) {
  if (strTopic == "myhome/Audio_Amplifier/save") {
    if (strPayload == "true") {
      Save();
      client.publish("myhome/Audio_Amplifier/save", "false");
    }
  }
  if (strTopic == "myhome/Audio_Amplifier/shtd") {
    if (strPayload == "true") {
      digitalWrite(PIN_SHTD, true);
      shtd = 1;
      client.publish("myhome/Audio_Amplifier/shtd", "true");
    } else {
      digitalWrite(PIN_SHTD, false);
      shtd = 0;
      client.publish("myhome/Audio_Amplifier/shtd", "false");
    }
  }
  if (strTopic == "myhome/Audio_Amplifier/fade") {
    if (strPayload == "true") {
      digitalWrite(PIN_FADE, true);
      fade = 1;
      client.publish("myhome/Audio_Amplifier/fade", "true");
    } else {
      digitalWrite(PIN_FADE, false);
      fade = 0;
      client.publish("myhome/Audio_Amplifier/fade", "false");
    }
  }
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
  int int_Payload;
  if (strTopic == "myhome/Audio_Amplifier/vol_1") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_1, int_Payload);
      vol_1 = int_Payload;
      client.publish("myhome/Audio_Amplifier/vol_1", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_2") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_2, int_Payload);
      vol_2 = int_Payload;
      client.publish("myhome/Audio_Amplifier/vol_2", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_3") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_3, int_Payload);
      vol_3 = int_Payload;
      client.publish("myhome/Audio_Amplifier/vol_3", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_4") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_4, int_Payload);
      vol_4 = int_Payload;
      client.publish("myhome/Audio_Amplifier/vol_4", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_5") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_5, int_Payload);
      vol_5 = int_Payload;
      client.publish("myhome/Audio_Amplifier/vol_5", ToChar(strPayload));
    }
  }
}
