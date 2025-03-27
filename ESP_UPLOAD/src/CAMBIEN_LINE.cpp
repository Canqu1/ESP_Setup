
#include "CAMBIEN_LINE.h"
void CAMBIEN_LINE_SETUP(int sensorLINE){
    Wire.begin(); // Khởi tạo giao tiếp I2C
    pcf8575.begin(); // Khởi tạo PCF8574
    pcf8575.pinMode(sensorLINE, INPUT); // Cấu hình chân P5 làm INPUT với pull-up nội bộ
    Serial.begin(115200); 
}
int CAMBIEN_LINE_DOC(int sensorLINE) {
    int reading = pcf8575.digitalRead(sensorLINE); 
    Serial.println(reading);
    return reading;
}
