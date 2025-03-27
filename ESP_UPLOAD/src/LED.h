#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>

// Định nghĩa số lượng LED và chân dữ liệu
#define N 8
#define DATA_PIN 27
#define BRIGHTNESS 255
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

// Khai báo mảng LED
extern CRGB leds[N];

// Khai báo bảng màu và chế độ pha trộn
extern CRGBPalette16 currentPalette;
extern TBlendType currentBlending;

// Prototype các hàm
void LED_setup();
uint8_t mapBrightness(int inputBrightness);
void LED_NUMBER(int STT_LED, int MAU, int DO_SANG);
void SetupTotallyRandomPalette();
void SetupBlackAndWhiteStripedPalette();
void SetupPurpleAndGreenPalette();
void ChangePalettePeriodically();
void FillLEDsFromPaletteColors(uint8_t colorIndex);
void runLedEffect(int effectType, unsigned long duration);

#endif // LED_H