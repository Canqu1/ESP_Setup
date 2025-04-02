#ifndef MP3_H
#define MP3_H

#include <Arduino.h>
#include <SD.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// Định nghĩa chân
#define SD_CS 5    // Chân CS cho SD card
#define DAC_PIN 25 // Chân DAC1 của ESP32

// Khai báo các biến toàn cục
extern String songs[20]; // Danh sách bài hát
extern int totalSongs;    // Tổng số bài hát
extern int currentSong;   // Bài hát hiện tại

// Prototype các hàm
void mp3_setup();
void play(String filePath);
void StopPlaying();
void mp3Task(int songIndex);

#endif // MP3_H