#ifndef ESP_CAM_H
#define ESP_CAM_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_camera.h"

// Các biến toàn cục
extern String Feedback;
extern String Command, cmd, P1, P2, P3, P4, P5, P6, P7, P8, P9;
extern byte ReceiveState, cmdState, strState, questionstate, equalstate, semicolonstate;

// Prototype các hàm
void espcam_setup();
void espcam_loop();
String tcp_http(String domain, String request, int port, byte wait);
String tcp_https(String domain, String request, int port, byte wait);
String LineNotify(String token, String request, byte wait);
String sendCapturedImageToLineNotify(String token);
void ExecuteCommand();
void getCommand(char c);

#endif // ESP_CAM_H