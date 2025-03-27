#ifndef CAMBIEN_LINE_H
#define CAMBIEN_LINE_H

#include <Arduino.h>
#include <Wire.h>
#include <Pcf8575.h>


enum LINE_PIN {
    sensorLINE_1 = P4,
    sensorLINE_2 = P5,
    sensorLINE_3 = P6,
    sensorLINE_4 = P7,
    sensorLINE_5 = P8,
    sensorLINE_6 = P9,
};

// Khai báo đối tượng PCF8574
extern PCF8575 pcf8575;

// Prototype các hàm
void CAMBIEN_LINE_SETUP(int sensorLINE );
int CAMBIEN_LINE_DOC(int sensorLINE);

#endif // CAMBIEN_CHAM_H