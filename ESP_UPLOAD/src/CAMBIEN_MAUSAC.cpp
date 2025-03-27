#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include <CAMBIEN_MAUSAC.h>
#include <Adafruit_Sensor.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();
void CAMBIEN_MAUSAC_SETUP() {
  Serial.begin(115200);
  if (tcs.begin()) {
    Serial.println("Cảm biến hoạt động");
  } else {
    Serial.println("Không thể kết nối với cảm biến, hãy kiểm tra kết nối...");
    while(1);
  }
}

int MAU_CAMBIEN_MAUSAC() {
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  if (c > r && c > g && c > b && lux > 500) {
    Serial.println("0"); // Không có màu
    return 0;
  } else if (r > g && r > b && r < c && lux > 10 && lux < 100) {
    Serial.println("1"); // Màu ĐỎ
    return 1;
  } else if (g > r && g > b && g < c && lux > 200 && lux < 300) {
    Serial.println("2"); // Màu XANH LÁ CÂY
    return 2;
  } else if (b > r && b > g && b < c && lux > 100 && lux < 200) {
    Serial.println("3"); // Màu XANH DƯƠNG
    return 3;
  } else {
    Serial.println("-1"); // Không xác định
    return -1;
  }
}