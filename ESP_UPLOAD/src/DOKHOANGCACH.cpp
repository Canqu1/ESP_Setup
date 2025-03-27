const int trig = 32; //Khai báo chân trig nối với chân số 8 là hằng số
const int echo = 33; //Khai báo chân echo nối với chân số 7 là hằng số
#include <Arduino.h>
void dokhoangcach_setup()
{
  Serial.begin(115200); 
  pinMode(trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(echo, INPUT); //Chân echo nhận tín hiệu
}

int read_khoangcach()
{
  int khoangcach;
  unsigned long thoigian;

  // Phát xung từ chân trig, độ rộng tối thiểu là 10ms
  digitalWrite(trig, 0); // Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig, 1); // Bật chân trig để phát xung
  delayMicroseconds(10); // Xung có độ rộng là 10 microsecond
  digitalWrite(trig, 0);

  thoigian = pulseIn(echo, HIGH, 30000);
  khoangcach = int(thoigian / 2 / 29.412); 

  Serial.print("Thoi gian: ");
  Serial.print(thoigian);
  Serial.println(" us");
  Serial.print("Khoang cach: ");
  Serial.println(khoangcach);

  return khoangcach;
}