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
  if (strTopic == "myhome/Audio_Amplifier/11") {
    client.publish("myhome/Audio_Amplifier/11", ToChar(strPayload));  
  }
  //////////////////////////
  
}
