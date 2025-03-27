#ifndef CAMBIEN_MAUSAC_H
#define CAMBIEN_MAUSAC_H

#include <Arduino.h>
#include <Adafruit_TCS34725.h>
#include <Wire.h>
// Khai báo đối tượng cảm biến màu sắc
extern Adafruit_TCS34725 tcs;

// Prototype các hàm
void CAMBIEN_MAUSAC_SETUP();
int MAU_CAMBIEN_MAUSAC();

#endif // CAMBIEN_MAUSAC_H