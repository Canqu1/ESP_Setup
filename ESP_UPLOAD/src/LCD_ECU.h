#ifndef LCD_ECU_H
#define LCD_ECU_H
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Pcf8575.h>
#include <Wire.h>

// Khai báo đối tượng PCF8575 và TFT_eSPI
extern PCF8575 pcf8575;
extern TFT_eSPI tft;

// Khai báo các biến toàn cục
extern int trangHienTai;
extern int mucMenu;
extern volatile boolean NUT_NHAN;

// Prototype các hàm
void lcd_setup();
void lcd_loop();
void khiNutLenDuocNhan();
void khiNutOkDuocNhan();
void khiNutXuongDuocNhan();
void khiNutBackDuocNhan();
int loop_botton(int &trangHienTai, int &mucMenu);
void menu(int menu, int line);
void IRAM_ATTR ISR_PCF8575();

#endif // LCD_ECU_H