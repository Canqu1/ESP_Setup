#include "CAMBIEN_CHAM.h"
 int lastButtonState = HIGH;
 unsigned long lastDebounceTime = 0;
 const unsigned long debounceDelay = 25;
void CAMBIEN_CHAM_SETUP(int sensorcham){
    Wire.begin(); // Khởi tạo giao tiếp I2C
    pcf8575.begin(); // Khởi tạo pcf8575
    pcf8575.pinMode(sensorcham, INPUT_PULLUP); // Cấu hình chân P5 làm INPUT với pull-up nội bộ
    Serial.begin(9600); 
}
void CAMBIEN_CHAM_LOOP(int sensorcham){
    int reading = pcf8575.digitalRead(sensorcham); // Đọc giá trị từ cảm biến // Đọc trạng thái nút

    // Nếu trạng thái thay đổi, ghi nhận thời gian
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    // Chờ đủ thời gian debounce để xác nhận thay đổi
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading == 0) {
            Serial.println("Nut nhan duoc nhan!");
        } else {
            Serial.println("Nut nhan khong duoc nhan.");
        }
    }

    lastButtonState = reading;  // Cập nhật trạng thái trước đó
}
