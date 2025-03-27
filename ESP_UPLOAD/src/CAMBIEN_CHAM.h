#ifndef CAMBIEN_CHAM_H
#define CAMBIEN_CHAM_H

#include <Arduino.h>
#include <Wire.h>
#include <Pcf8575.h>

// Khai báo các chân cảm biến chạm
extern int lastButtonState;
extern unsigned long lastDebounceTime;
extern const unsigned long debounceDelay;
enum CHAM_PIN {
    sensorcham_1 = P4,
    sensorcham_2 = P5,
    sensorcham_3 = P6,
    sensorcham_4 = P7,
    sensorcham_5 = P8,
    sensorcham_6 = P9,

};

// Khai báo đối tượng PCF8574
extern PCF8575 pcf8575;

// Prototype các hàm
void CAMBIEN_CHAM_SETUP(int sensorcham);
void CAMBIEN_CHAM_LOOP(int sensorcham);

#endif // CAMBIEN_CHAM_H