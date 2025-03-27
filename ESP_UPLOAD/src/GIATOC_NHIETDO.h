#ifndef GIATOC_NHIETDO_H
#define GIATOC_NHIETDO_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Khai báo đối tượng MPU6050
extern Adafruit_MPU6050 mpu;

// Prototype các hàm
void setupMPU6050();
float readAccelX();
float readAccelY();
float readAccelZ();
float readGyroX();
float readGyroY();
float readGyroZ();
float readTemperature();

#endif // GIATOC_NHIETDO_H