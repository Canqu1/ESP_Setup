#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "PCA9685.h"

// Khởi tạo đối tượng PWM
Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver(0x40);

// Biến toàn cục
int currentVelocity = 100; // Tốc độ mặc định (0-100%)

// Hàm điều khiển servo
void servo_reset(int port) {
  PWM.setPWM(port, 0, 102);
}

void servo_port(int port, int goc_bandau, int goc_ketthuc) {
  int goc_bandau_fix = map(goc_bandau, 0, 180, 102, 623);
  int goc_ketthuc_fix = map(goc_ketthuc, 0, 180, 102, 623);
  PWM.setPWM(port, 0, goc_bandau_fix);
  delay(500);
  PWM.setPWM(port, 0, goc_ketthuc_fix);
  delay(500);
}

// Hàm điều khiển motor
void move_forward_motor(int move_port, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port, 0, pwmValue);
  PWM.setPWM(move_port + 1, 0, 0); // AIA → Kênh 0
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port, 0, 0);
    PWM.setPWM(move_port + 1, 0, 0);
  }
}

void move_backward_motor(int move_port, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port + 1, 0, pwmValue); // BIB → Kênh 3, luôn HI
  PWM.setPWM(move_port, 0, 0); // AIA → Kênh 0
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port, 0, 0);
    PWM.setPWM(move_port + 1, 0, 0);
  }
}

void move_backward_motor_double(int move_port1, int move_port2, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port1 + 1, 0, pwmValue); // AIA → Kênh 0
  PWM.setPWM(move_port1, 0, 0); // BIB → Kênh 3, luôn HI
  PWM.setPWM(move_port2 + 1, 0, pwmValue); // AIA → Kênh 0
  PWM.setPWM(move_port2, 0, 0); // BIB → Kênh 3, luôn HI
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port1, 0, 0);
    PWM.setPWM(move_port1 + 1, 0, 0);
    PWM.setPWM(move_port2, 0, 0);
    PWM.setPWM(move_port2 + 1, 0, 0);
  }
}

void move_forward_motor_double(int move_port1, int move_port2, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port1 + 1, 4095, 0); // AIA → Kênh 0
  PWM.setPWM(move_port1, 0, pwmValue); // AIB → Kênh 1, luôn HI
  PWM.setPWM(move_port2 + 1, 4095, 0); // AIA → Kênh 0
  PWM.setPWM(move_port2, 0, pwmValue); // AIB → Kênh 1, luôn HI
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port1, 0, 0);
    PWM.setPWM(move_port1 + 1, 0, 0);
    PWM.setPWM(move_port2, 0, 0);
    PWM.setPWM(move_port2 + 1, 0, 0);
  }
}

void move_right_motor(int move_port1, int move_port2, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port1, 0, pwmValue); // AIA → Kênh 0
  PWM.setPWM(move_port1 + 1, 0, 0); // BIB → Kênh 3, luôn HI
  PWM.setPWM(move_port2 + 1, 0, 0); // AIA → Kênh 0
  PWM.setPWM(move_port2, 0, 0); // BIB → Kênh 3, luôn HI
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port1, 0, 0);
    PWM.setPWM(move_port1 + 1, 0, 0);
    PWM.setPWM(move_port2, 0, 0);
    PWM.setPWM(move_port2 + 1, 0, 0);
  }
}

void move_left_motor(int move_port1, int move_port2, int SPEED, int time) {
  SPEED = SPEED * 2.55; // Giới hạn dc từ 0-255
  uint16_t pwmValue = (SPEED * 4095 / 255); // Chuyển đổi và đảo ngược
  PWM.setPWM(move_port1 + 1, 0, 0); // AIA → Kênh 0
  PWM.setPWM(move_port1, 0, 0); // BIB → Kênh 3, luôn HI
  PWM.setPWM(move_port2 + 1, 0, 0); // AIA → Kênh 0
  PWM.setPWM(move_port2, 0, pwmValue); // BIB → Kênh 3, luôn HI
  if (time != 0) {
    delay(time);
    PWM.setPWM(move_port1, 0, 0);
    PWM.setPWM(move_port1 + 1, 0, 0);
    PWM.setPWM(move_port2, 0, 0);
    PWM.setPWM(move_port2 + 1, 0, 0);
  }
}

void PWM_BEGIN() {
  PWM.begin();
  PWM.setOscillatorFrequency(27000000);
  PWM.setPWMFreq(60);
}

void SR04_BEGIN(int trig, int echo) {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

// Hàm mới: Drive(forward/reverse)
void driveForward() {
  move_forward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, 1000); // Chạy 1000ms
}

void driveReverse() {
  move_backward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, 1000); // Chạy 1000ms
}

// Hàm mới: Drive(forward/reverse) for(mm)
void driveForwardForDistance(int distance_mm) {
  float speedFactor = currentVelocity / 100.0;
  float mmPerMs = MM_PER_MS_AT_100_PERCENT * speedFactor;
  int time_ms = (int)(distance_mm / mmPerMs);
  move_forward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, time_ms);
}

void driveReverseForDistance(int distance_mm) {
  float speedFactor = currentVelocity / 100.0;
  float mmPerMs = MM_PER_MS_AT_100_PERCENT * speedFactor;
  int time_ms = (int)(distance_mm / mmPerMs);
  move_backward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, time_ms);
}

// Hàm mới: Turn(right/left)
void turnRight() {
  move_right_motor(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, 500); // Rẽ trong 500ms
}

void turnLeft() {
  move_left_motor(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, 500); // Rẽ trong 500ms
}

// Hàm mới: Turn(right/left) to() degree
void turnRightToDegrees(int degrees) {
  float speedFactor = currentVelocity / 100.0;
  float degreesPerMs = DEGREES_PER_MS_AT_100_PERCENT * speedFactor;
  int time_ms = (int)(degrees / degreesPerMs);
  move_right_motor(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, time_ms);
}

void turnLeftToDegrees(int degrees) {
  float speedFactor = currentVelocity / 100.0;
  float degreesPerMs = DEGREES_PER_MS_AT_100_PERCENT * speedFactor;
  int time_ms = (int)(degrees / degreesPerMs);
  move_left_motor(port_dc_motor_1_1, port_dc_motor_2_1, currentVelocity, time_ms);
}

// Hàm mới: Stop all
void stopAll() {
  move_forward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, 0, 0);
}

// Hàm mới: Set velocity()% for all
void setVelocity(int velocity) {
  if (velocity >= 0 && velocity <= 100) {
    currentVelocity = velocity;
  }
}

// Hàm mới: Lấy tốc độ hiện tại
int getCurrentVelocity() {
  return currentVelocity;
}