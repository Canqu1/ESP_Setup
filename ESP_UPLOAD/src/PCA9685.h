#ifndef PCA9685_H
#define PCA9685_H

enum {
    port_servo_0 = 0,
    port_servo_1 = 1,
    port_servo_2 = 2,
    port_servo_3 = 3,
    port_dc_motor_1_1 = 4,
    port_dc_motor_1_2 = 5,
    port_dc_motor_2_1 = 6,
    port_dc_motor_2_2 = 7,
    port_dc_motor_3_1 = 8,
    port_dc_motor_3_2 = 9,
    port_dc_motor_4_1 = 10,
    port_dc_motor_4_2 = 11,
};
const float WHEEL_DIAMETER_MM = 65.0; // Đường kính bánh xe (mm)
const float WHEEL_CIRCUMFERENCE_MM = WHEEL_DIAMETER_MM * 3.14; // Chu vi bánh xe (mm)
const float RPM_AT_100_PERCENT = 100.0; // Số vòng quay/phút tại tốc độ 100%
const float MM_PER_MS_AT_100_PERCENT = (RPM_AT_100_PERCENT * WHEEL_CIRCUMFERENCE_MM) / 60000.0; // mm/ms tại 100%
const float WHEEL_BASE_MM = 120.0; // Khoảng cách giữa hai bánh xe (mm)
const float DEGREES_PER_MS_AT_100_PERCENT = (RPM_AT_100_PERCENT * 360.0) / (60000.0 * (WHEEL_BASE_MM / 2.0)); // Độ/ms tại 100%

// Khai báo các hàm
void PWM_BEGIN();
void SR04_BEGIN(int trig, int echo);
void servo_reset(int port);
void servo_port(int port, int goc_bandau, int goc_ketthuc);
void move_forward_motor(int move_port, int SPEED, int time);
void move_backward_motor(int move_port, int SPEED, int time);
void move_forward_motor_double(int move_port1, int move_port2, int SPEED, int time);
void move_backward_motor_double(int move_port1, int move_port2, int SPEED, int time);
void move_right_motor(int move_port1, int move_port2, int SPEED, int time);
void move_left_motor(int move_port1, int move_port2, int SPEED, int time);

// Hàm mới
void driveForward();
void driveReverse();
void driveForwardForDistance(int distance_mm);
void driveReverseForDistance(int distance_mm);
void turnRight();
void turnLeft();
void turnRightToDegrees(int degrees);
void turnLeftToDegrees(int degrees);
void stopAll();
void setVelocity(int velocity);
int getCurrentVelocity();

#endif