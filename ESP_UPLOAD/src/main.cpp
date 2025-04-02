#include "PCA9685.h"
#include <Arduino.h>
#include "CAMBIEN_LINE.h"
#include "CAMBIEN_MAUSAC.h"
#include "DOKHOANGCACH.h"
#include "CAMBIEN_CHAM.h"
#include "LED.h"
#include "LCD_ECU.h"
#include "MP3.h"
void processCommand(String command);

void setup() {
  Serial.begin(115200);
  dokhoangcach_setup();
  PWM_BEGIN();
  setVelocity(100);
  stopAll();
  servo_reset(port_servo_0);
  servo_reset(port_servo_1);
  servo_reset(port_servo_2);
  CAMBIEN_LINE_SETUP(sensorLINE_1);
  lcd_setup();
  LED_setup();
  mp3_setup();
}

void loop()
{
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.length() > 0) {
      processCommand(command);
    }
  }
}

void processCommand(String command) {
  if (command.startsWith("DRIVE")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String direction = command.substring(firstSpace + 1);
      int secondSpace = direction.indexOf(' ');
      if (secondSpace != -1) {
        // DRIVE FWD/REV {distance}
        String dir = direction.substring(0, secondSpace);
        String distanceStr = direction.substring(secondSpace + 1);
        int distance = distanceStr.toInt();
        if (dir == "FWD") {
          driveForwardForDistance(distance);
          Serial.println("DRIVE_FWD_OK");
        } else if (dir == "REV") {
          driveReverseForDistance(distance);
          Serial.println("DRIVE_REV_OK");
        } else {
          Serial.println("INVALID_DIRECTION");
        }
      } else {
        // DRIVE FWD/REV
        if (direction == "FWD") {
          driveForward();
          Serial.println("DRIVE_FWD_OK");
        } else if (direction == "REV") {
          driveReverse();
          Serial.println("DRIVE_REV_OK");
        } else {
          Serial.println("INVALID_DIRECTION");
        }
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  } else if (command.startsWith("TURN")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String direction = command.substring(firstSpace + 1);
      int secondSpace = direction.indexOf(' ');
      if (secondSpace != -1) {
        // TURN RIGHT/LEFT {degrees}
        String dir = direction.substring(0, secondSpace);
        String degreesStr = direction.substring(secondSpace + 1);
        int degrees = degreesStr.toInt();
        if (dir == "RIGHT") {
          turnRightToDegrees(degrees);
          Serial.println("TURN_RIGHT_OK");
        } else if (dir == "LEFT") {
          turnLeftToDegrees(degrees);
          Serial.println("TURN_LEFT_OK");
        } else {
          Serial.println("INVALID_DIRECTION");
        }
      } else {
        // TURN RIGHT/LEFT
        if (direction == "RIGHT") {
          turnRight();
          Serial.println("TURN_RIGHT_OK");
        } else if (direction == "LEFT") {
          turnLeft();
          Serial.println("TURN_LEFT_OK");
        } else {
          Serial.println("INVALID_DIRECTION");
        }
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  } else if (command == "STOP_ALL") {
    stopAll();
    Serial.println("STOP_ALL_OK");
  } else if (command.startsWith("SET_VELOCITY")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String velocityStr = command.substring(firstSpace + 1);
      int velocity = velocityStr.toInt();
      if (velocity >= 0 && velocity <= 100) {
        setVelocity(velocity);
        Serial.println("SET_VELOCITY_OK");
      } else {
        Serial.println("INVALID_VELOCITY");
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  }else if (command == "READ_DISTANCE_SENSOR") {
   int distance= read_khoangcach();
  } else if (command == "READ_COLOR_SENSOR") {
    int color = MAU_CAMBIEN_MAUSAC();
  }
  else if (command == "FWD") { 
    int velocity = getCurrentVelocity();
    move_forward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, velocity, 1000);
    Serial.println("FWD_OK");
  } else if (command == "BWD") {
    move_backward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, getCurrentVelocity(), 1000);
    Serial.println("BWD_OK");
  } else if (command == "STOP") { 
    move_forward_motor_double(port_dc_motor_1_1, port_dc_motor_2_1, 0, 0);
    Serial.println("STOP_OK");
  } else if (command.startsWith("TEST_SERVO")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String params = command.substring(firstSpace + 1);
      int secondSpace = params.indexOf(' ');
      
      String portStr;
      String angleStr;
      if (secondSpace != -1) {
        // TEST_SERVO {port} {angle}
        portStr = params.substring(0, secondSpace);
        angleStr = params.substring(secondSpace + 1);
      } else {
        // TEST_SERVO {port}
        portStr = params;
        angleStr = "";
      }

      int port = portStr.toInt();
      if (port < 0 || port > 2) {
        Serial.println("INVALID_SERVO_PORT");
        return;
      }

      int servoPort;
      switch (port) {
        case 0: servoPort = port_servo_0; break;
        case 1: servoPort = port_servo_1; break;
        case 2: servoPort = port_servo_2; break;
        default: 
          Serial.println("INVALID_SERVO_PORT");
          return;
      }

      if (secondSpace != -1) {
        int angle = angleStr.toInt();
        if (angle >= 0 && angle <= 180) {
          servo_port(servoPort, angle, angle);
          delay(500);
          Serial.println("SERVO_TEST_OK");
        } else {
          Serial.println("INVALID_ANGLE");
        }
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  } else if (command.startsWith("READ_LINE_SENSOR")) {
    int spaceIndex = command.indexOf(' ');
    if (spaceIndex == -1) {
      Serial.println("Error: Invalid command format");
      return;
    }

    String portStr = command.substring(spaceIndex + 1);
    int port = portStr.toInt();
    if (port == 0 && portStr != "0") {
      Serial.println("Error: Invalid port format (must be a number)");
      return;
    }

    int sensorLINE;
    switch (port) {
      case 1:
        sensorLINE = sensorLINE_1;
        break;
      case 2:
        sensorLINE = sensorLINE_2;
        break;
      case 3:
        sensorLINE = sensorLINE_3;
        break;
      case 4:
        sensorLINE = sensorLINE_4;
        break;
      default:
        Serial.println("Error: Invalid port (must be 1, 2, 3, or 4)");
        return;
    }
    CAMBIEN_LINE_DOC(sensorLINE);
 
  } else if (command.startsWith("READ_TOUCH_SENSOR")) {
    int spaceIndex = command.indexOf(' ');
    if (spaceIndex == -1) {
      Serial.println("Error: Invalid command format");
      return;
    }

    String portStr = command.substring(spaceIndex + 1);
    int port = portStr.toInt();
    if (port == 0 && portStr != "0") {
      Serial.println("Error: Invalid port format (must be a number)");
      return;
    }
    int touchSensor;
    switch (port) {
      case 1:
        touchSensor = sensorcham_1;
        break;
      case 2:
        touchSensor = sensorcham_2;
        break;
      case 3:
        touchSensor = sensorcham_3;
        break;
      case 4:
        touchSensor = sensorcham_4;
        break;
      default:
        Serial.println("Error: Invalid port (must be 1, 2, 3, or 4)");
        return;
    }
  } else if (command.startsWith("LED")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String params = command.substring(firstSpace + 1);
      int secondSpace = params.indexOf(' ');
      
      if (secondSpace != -1) {
        String effectStr = params.substring(0, secondSpace);
        String durationStr = params.substring(secondSpace + 1);
        
        int effectType = effectStr.toInt();
        unsigned long duration = durationStr.toInt();
        
        if (effectType >= 0 && effectType <= 4) {
          runLedEffect(effectType, duration);
          Serial.println("LED_OK");
        } else {
          Serial.println("INVALID_EFFECT_TYPE");
        }
      } else {
        Serial.println("INVALID_LED_FORMAT");
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  } 
  else if (command.startsWith("PLAY_MP3")) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
      String params = command.substring(firstSpace + 1);
      int songIndex = params.toInt();
  
      // Kiểm tra tính hợp lệ của chỉ mục bài hát
      if (songIndex >= 0 && songIndex < totalSongs) {
        mp3Task(songIndex);
        Serial.println("MP3_OK");
      } else {
        Serial.println("INVALID_SONG_INDEX");
      }
    } else {
      Serial.println("INVALID_CMD_FORMAT");
    }
  }
  else {
    Serial.println("UNKNOWN_CMD");
  }
}