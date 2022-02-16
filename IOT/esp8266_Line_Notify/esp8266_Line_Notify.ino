#include "EEPROM.h"
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include <Time.h>

//const String month_name[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
//const String day_name[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

const String month_name[12] = {"เดือนมกราคม", "เดือนกุมภาพันธ์", "เดือนมีนาคม", "เดือนเมษายน", "เดือนพฤษภาคม", "เดือนมิถุนายน", "เดือนกรกฎาคม", "เดือนสิงหาคม", "เดือนกันยายน", "เดือนตุลาคม", "เดือนพฤศจิกายน", "เดือนธันวาคม"};

const String day_name[7] = {"วันอาทิตย์", "วันจันทร์ ", "วันอังคาร", "วันพุธ", "วันพฤหัสบดี", "วันศุกร์", "วันเสาร์"};
int timezone = 7 * 3600; //ตั้งค่า TimeZone ตามเวลาประเทศไทย
int led1 = D2, led2 = D3;
int dst = 0; //กำหนดค่า Date Swing Time
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(3000);
  EEPROM.begin(512);
  //setwifi();
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  delay(3000);
  Serial.println("START");
  if (digitalRead(D0) == 0) {
    Serial.println("AP MODE");
    setwifi();
  } else {
    Serial.println("CL MODE");
    Connect();
  }
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov"); //ดึงเวลาจาก Server
  while (!time(nullptr)) {

    Serial.print("*");

    delay(1000);

  }
  Serial.println("");

}
void loop() {
  time_t now = time(nullptr);

  struct tm* p_tm = localtime(&now);
  String date_time = day_name[(p_tm->tm_wday)] + " ที่ " + String(p_tm->tm_mday) + " " + month_name[(p_tm->tm_mon)] + " พ.ศ." + String(p_tm->tm_year + 2443) + " เวลา " + String(p_tm->tm_hour) + ":" + String(p_tm->tm_min) + ":" + String(p_tm->tm_sec)+" น.";
  //Serial.println(date_time);
  // delay(1000);
  if (digitalRead(D1) == 0) {
    //LINE.notify("แจ้งเตือน..ขณะนี้ได้มีการเปิดคลังอาวุธ ศฝ.นศท.มทบ.23");
    LINE.notifyPicture("ขณะนี้ได้มีการเปิดคลังอาวุธ ศฝ.นศท.มทบ.23\n"+date_time, "https://raw.githubusercontent.com/WATCHARAPHON69/IOT/main/IOT/esp8266_Line_Notify/img.jpg");
    //LINE.notify(date_time);
    Serial.println("ตรวจพบความเคลื่อนไหว");
    while (digitalRead(D1) == 0);
  }
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led1, 1);
    delay(100);
    digitalWrite(led1, 0);
    delay(100);
  }
  digitalWrite(led1, 1);

}
