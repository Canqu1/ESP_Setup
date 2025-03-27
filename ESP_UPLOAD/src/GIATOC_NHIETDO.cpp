#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Hàm khởi tạo MPU6050
void setupMPU6050() {
    Serial.begin(9600);
    while (!Serial) {
        delay(10); // Chờ Serial khởi động
    }

    // Thử khởi tạo MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    // Thiết lập phạm vi gia tốc kế ±8g
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    // Thiết lập phạm vi con quay hồi chuyển ±500°/s
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    // Thiết lập băng thông bộ lọc 21 Hz
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    delay(100); // Đợi ổn định
}

// --- Hàm đọc gia tốc (Acceleration) ---
// Đọc gia tốc trục X
float readAccelX() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Gia tốc trục X: ");
    Serial.print(a.acceleration.x);
    Serial.println(" m/s^2");

    return a.acceleration.x;
}

// Đọc gia tốc trục Y
float readAccelY() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Gia tốc trục Y: ");
    Serial.print(a.acceleration.y);
    Serial.println(" m/s^2");

    return a.acceleration.y;
}

// Đọc gia tốc trục Z
float readAccelZ() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Gia tốc trục Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    return a.acceleration.z;
}

// --- Hàm đọc con quay hồi chuyển (Gyro) ---
// Đọc con quay trục X
float readGyroX() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Con quay trục X: ");
    Serial.print(g.gyro.x);
    Serial.println(" rad/s");

    return g.gyro.x;
}

// Đọc con quay trục Y
float readGyroY() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Con quay trục Y: ");
    Serial.print(g.gyro.y);
    Serial.println(" rad/s");

    return g.gyro.y;
}

// Đọc con quay trục Z
float readGyroZ() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Con quay trục Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    return g.gyro.z;
}

// --- Hàm đọc nhiệt độ ---
float readTemperature() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Nhiệt độ: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");

    return temp.temperature;
}
