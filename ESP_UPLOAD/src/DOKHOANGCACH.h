#ifndef DOKHOANGCACH_H
#define DOKHOANGCACH_H

#include <Arduino.h>

// Khai báo chân trig và echo
extern const int trig;
extern const int echo;

// Prototype các hàm
void dokhoangcach_setup();
int read_khoangcach();

#endif // DOKHOANGCACH_H