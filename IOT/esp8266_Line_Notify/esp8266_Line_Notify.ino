#include "EEPROM.h"
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
void setup() {
  Serial.begin(115200);
  delay(3000);
  EEPROM.begin(512);
  //setwifi();
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  delay(3000);
  Serial.println("START");
  if (digitalRead(D0) == 0) {
    Serial.println("AP MODE");
    setwifi();
  } else {
    Serial.println("CL MODE");
    Connect();
  }
}
void loop() {
  if (digitalRead(D1) == 0) {


    LINE.notifyPicture("ตรวจพบความเคลื่อนไหว", "https://raw.githubusercontent.com/WATCHARAPHON69/IOT/main/IOT/esp8266_Line_Notify/img.jpg");
    Serial.println("ตรวจพบความเคลื่อนไหว");
    while (digitalRead(D1) == 0);
  }
}
