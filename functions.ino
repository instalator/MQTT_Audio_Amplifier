//--------------------------------- Functions ---------------------------------//
void callback_iobroker(String strTopic, String strPayload) {
    if (strPayload == "true") {
      Save();
      mqtt.publish("myhome/Audio_Amplifier/save", "false");
    }
  if (strTopic == "myhome/Audio_Amplifier/shtd") {
    if (strPayload == "true") {
      digitalWrite(PIN_SHTD, HIGH);
      shtd = 1;
    } else {
      digitalWrite(PIN_SHTD, LOW);
      shtd = 0;
    }
    mqtt.publish("myhome/Audio_Amplifier/shtd", IntToBool(shtd));
  }
  if (strTopic == "myhome/Audio_Amplifier/fade") {
    if (strPayload == "true") {
      digitalWrite(PIN_FADE, HIGH);
      fade = 1;
    } else {
      digitalWrite(PIN_FADE, LOW);
      fade = 0;
    }
    mqtt.publish("myhome/Audio_Amplifier/fade", IntToBool(fade));
  }
  if (strTopic == "myhome/Audio_Amplifier/zone_1") {
    if (strPayload == "false") {
      digitalWrite(PIN_AMP_1, HIGH);
      mqtt.publish("myhome/Audio_Amplifier/zone_1", "false");
    } else {
      digitalWrite(PIN_AMP_1, LOW);
      mqtt.publish("myhome/Audio_Amplifier/zone_1", "true");
    }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_2") {
    if (strPayload == "false") {
      digitalWrite(PIN_AMP_2, HIGH);
      mqtt.publish("myhome/Audio_Amplifier/zone_2", "false");
    } else {
      digitalWrite(PIN_AMP_2, LOW);
      mqtt.publish("myhome/Audio_Amplifier/zone_2", "true");
    }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_3") {
    if (strPayload == "false") {
      digitalWrite(PIN_AMP_3, HIGH);
      mqtt.publish("myhome/Audio_Amplifier/zone_3", "false");
    } else {
      digitalWrite(PIN_AMP_3, LOW);
      mqtt.publish("myhome/Audio_Amplifier/zone_3", "true");
    }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_4") {
    if (strPayload == "false") {
      digitalWrite(PIN_AMP_4, HIGH);
      mqtt.publish("myhome/Audio_Amplifier/zone_4", "false");
    } else {
      digitalWrite(PIN_AMP_4, LOW);
      mqtt.publish("myhome/Audio_Amplifier/zone_4", "true");
    }
  }
  //////////////////////////
  else if (strTopic == "myhome/Audio_Amplifier/zone_5") {
    if (strPayload == "false") {
      digitalWrite(PIN_AMP_5, HIGH);
      mqtt.publish("myhome/Audio_Amplifier/zone_5", "false");
    } else {
      digitalWrite(PIN_AMP_5, LOW);
      mqtt.publish("myhome/Audio_Amplifier/zone_5", "true");
    }
  }
  /////////////////////////////////////////////////////////
  int int_Payload;
  if (strTopic == "myhome/Audio_Amplifier/vol_1") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_1, int_Payload);
      vol_1 = int_Payload;
      mqtt.publish("myhome/Audio_Amplifier/vol_1", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_2") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_2, int_Payload);
      vol_2 = int_Payload;
      mqtt.publish("myhome/Audio_Amplifier/vol_2", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_3") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_3, int_Payload);
      vol_3 = int_Payload;
      mqtt.publish("myhome/Audio_Amplifier/vol_3", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_4") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_4, int_Payload);
      vol_4 = int_Payload;
      mqtt.publish("myhome/Audio_Amplifier/vol_4", ToChar(strPayload));
    }
  }
  else if (strTopic == "myhome/Audio_Amplifier/vol_5") {
    int_Payload = strPayload.toInt();
    if (int_Payload >= 0 && int_Payload <= 255) {
      analogWrite(PIN_VOL_5, int_Payload);
      vol_5 = int_Payload;
      mqtt.publish("myhome/Audio_Amplifier/vol_5", ToChar(strPayload));
    }
  }
}

char* ToChar (String intstr) {
  intstr.toCharArray(b, 4);
  return b;
}
char* IntToChar (int intV) {
  String stringVar = String(intV, DEC);
  stringVar.toCharArray(b, 4);
  return b;
}
const char* IntToBool (int r) {
    if (r > 0){
      return "true";
    } else{
      return "false";
    }
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
