#include <Arduino.h>
#include <SD.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define SD_CS 5
#define DAC_PIN 25

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

String songs[20];
int totalSongs = 0;
int currentSong = -1;
void StopPlaying() {
  if (mp3) {
    mp3->stop();
    delete mp3;
    mp3 = NULL;
  }
  if (buff) {
    buff->close();
    delete buff;
    buff = NULL;
  }
  if (file) {
    file->close();
    delete file;
    file = NULL;
  }
  Serial.println("Đã dừng.");
}

void play(String filePath) {
  StopPlaying(); // Dừng và giải phóng trước khi phát mới
  file = new AudioFileSourceSD(filePath.c_str());
  if (!file->isOpen()) {
    Serial.print("Không thể mở file: ");
    Serial.println(filePath);
    return;
  }
  buff = new AudioFileSourceBuffer(file, 4096);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out);
  Serial.print("Đang phát: ");
  Serial.println(filePath);
}

void mp3Task(int songIndex) {
  // Lấy tham số từ pvParameters và ép kiểu về int

  // Kiểm tra tính hợp lệ của songIndex
  if (songIndex >= 0 && songIndex < totalSongs) {
    currentSong = songIndex;
    play(songs[currentSong]);
  } else {
    Serial.println("Số thứ tự bài hát không hợp lệ! Chọn từ 0 đến " + String(totalSongs - 1));
    currentSong = -1;
  }

  while (1) {
    if (mp3 && mp3->isRunning()) {
      if (!mp3->loop()) {
        Serial.println("Đã phát xong bài hát.");
        currentSong = -1; // Đặt lại để chờ logic khác nếu cần
      }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void mp3_setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SD.begin(SD_CS)) {
    Serial.println("Không thể khởi động SD card!");
    return;
  }
  Serial.println("SD card đã sẵn sàng.");

  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.endsWith(".mp3") || name.endsWith(".MP3")) {
      songs[totalSongs] = String("/") + name;
      Serial.print(totalSongs);
      Serial.print(": ");
      Serial.println(songs[totalSongs]);
      totalSongs++;
    }
    entry.close();
  }
  root.close();

  if (totalSongs == 0) {
    Serial.println("Không tìm thấy file MP3!");
    return;
  }

  out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
  out->SetPinout(0, 0, DAC_PIN);

  // Truyền tham số bài hát (ví dụ: 3) vào task
}


