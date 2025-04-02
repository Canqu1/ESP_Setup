#include <FastLED.h>
#include"LED.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define N 8
#define DATA_PIN 27
#define BRIGHTNESS 255
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[N];
#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType currentBlending;

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
    CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black,
    CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black,
    CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray,
    CRGB::Blue, CRGB::Blue, CRGB::Black, CRGB::Black
};


void LED_setup() {
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, N);
    FastLED.setBrightness(255);
}

uint8_t mapBrightness(int inputBrightness) {
  if (inputBrightness < 1 || inputBrightness > 100) {
    Serial.println("Loi: DO_SANG phai tu 1 den 100!");
    return 0;
  }
  return map(inputBrightness, 1, 100, 0, 255);
}

void LED_NUMBER(int STT_LED, int MAU, int DO_SANG) {
  if (STT_LED < 0 || STT_LED >= N) {
    Serial.println("Loi: STT_LED khong hop le!");
    return;
  }
  uint8_t mappedBrightness = mapBrightness(DO_SANG);
  uint8_t red = 0, green = 0, blue = 0;
  switch (MAU) {
    case 0: red = 255; green = 0; blue = 0; break;
    case 1: red = 0; green = 255; blue = 0; break;
    case 2: red = 0; green = 0; blue = 255; break;
    case 3: red = 255; green = 255; blue = 0; break;
    case 4: red = 255; green = 0; blue = 255; break;
    case 5: red = 0; green = 255; blue = 255; break;
    case 6: red = 255; green = 255; blue = 255; break;
    case 7: red = 255; green = 128; blue = 0; break;
    default: red = 0; green = 0; blue = 0; break;
  }
  float scale = mappedBrightness / 255.0;
  uint8_t adjustedRed = red * scale;
  uint8_t adjustedGreen = green * scale;
  uint8_t adjustedBlue = blue * scale;
  leds[STT_LED] = CRGB(adjustedRed, adjustedGreen, adjustedBlue);
  FastLED.show();
}

void SetupTotallyRandomPalette() {
  for (int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV(random8(), 255, random8());
  }
}

void SetupBlackAndWhiteStripedPalette() {
  fill_solid(currentPalette, 16, CRGB::Black);
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

void SetupPurpleAndGreenPalette() {
  CRGB purple = CHSV(HUE_PURPLE, 255, 255);
  CRGB green = CHSV(HUE_GREEN, 255, 255);
  CRGB black = CRGB::Black;
  currentPalette = CRGBPalette16(
    green, green, black, black,
    purple, purple, black, black,
    green, green, black, black,
    purple, purple, black, black
  );
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  uint8_t brightness = 255;
  for (int i = 0; i < N; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void ChangePalettePeriodically() {
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  if (lastSecond != secondHand) {
    lastSecond = secondHand;
    if (secondHand == 0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
    if (secondHand == 10) { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND; }
    if (secondHand == 15) { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
    if (secondHand == 20) { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
    if (secondHand == 25) { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
    if (secondHand == 30) { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
    if (secondHand == 35) { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
    if (secondHand == 40) { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
    if (secondHand == 45) { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
    if (secondHand == 50) { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND; }
    if (secondHand == 55) { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
  }
}

void runLedEffect(int effectType, unsigned long duration) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < duration) {
    switch (effectType) {
      case 0: { // Chase Effect
        static uint8_t colorIndex = 0;
        FillLEDsFromPaletteColors(colorIndex);
        colorIndex += 1; // Tăng chỉ số để tạo hiệu ứng dịch chuyển
        FastLED.show();
        vTaskDelay((1000 / UPDATES_PER_SECOND) / portTICK_PERIOD_MS);
        break;

      }
      case 1: { // Rainbow Effect with Palette Change
        static uint8_t colorIndex = 0;
        ChangePalettePeriodically();
        FillLEDsFromPaletteColors(colorIndex);
        colorIndex += 1;
        FastLED.show();
        vTaskDelay((1000 / UPDATES_PER_SECOND) / portTICK_PERIOD_MS);

        break;
      }
      case 2: { // Random Blink Effect
        SetupTotallyRandomPalette();
        for (int i = 0; i < N; i++) {
          if (random8(100) < 30) {
            uint8_t colorIndex = random8();
            leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
          } else {
            leds[i] = CRGB::Black;
          }
        }
        FastLED.show();
        vTaskDelay((1000 / UPDATES_PER_SECOND) / portTICK_PERIOD_MS);
        break;
      }
      case 3: { // Black and White Striped Palette
        SetupBlackAndWhiteStripedPalette();
        static uint8_t colorIndex = 0;
        FillLEDsFromPaletteColors(colorIndex);
        colorIndex += 1;
        FastLED.show();
        vTaskDelay((1000 / UPDATES_PER_SECOND) / portTICK_PERIOD_MS);
        break;
      }
      case 4: { // Purple and Green Palette
        SetupPurpleAndGreenPalette();
        static uint8_t colorIndex = 0;
        FillLEDsFromPaletteColors(colorIndex);
        colorIndex += 1;
        FastLED.show();
        vTaskDelay((1000 / UPDATES_PER_SECOND) / portTICK_PERIOD_MS);

        break;
      }
      default:
        Serial.println("Loi: effectType khong hop le!");
        return;
    }
  }
}