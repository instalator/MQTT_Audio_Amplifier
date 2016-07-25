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
            digitalWrite(17, true);
            client.publish("myhome/Audio_Amplifier/zone_1", "true");
        } else {
            digitalWrite(17, false);
            client.publish("myhome/Audio_Amplifier/zone_1", "false");
        }
  }
  //////////////////////////
  
}
