#include <Arduino.h>
#include <SD.h>   // Thư viện để đọc thẻ SD
#include "AudioFileSourceSD.h"      // Đọc file từ SD
#include "AudioFileSourceBuffer.h"  // Bộ đệm âm thanh
#include "AudioGeneratorMP3.h"      // Giải mã MP3
#include "AudioOutputI2S.h"         // Dùng I2S với DAC cho ESP32
#include "MP3.h"
// Định nghĩa chân
#define SD_CS 5    // Chân CS cho SD card
#define DAC_PIN 25 // Chân DAC1 của ESP32

// Khai báo đối tượng
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

// Danh sách bài hát
String songs[20]; // Giới hạn 20 bài (có thể tăng nếu cần)
int totalSongs = 0;
void play(String filePath) { // Hàm play nhận tham số String
  file = new AudioFileSourceSD(filePath.c_str()); // Đọc file MP3 từ SD
  if (!file->isOpen()) {
    Serial.print("Không thể mở file: ");
    Serial.println(filePath);
    return;
  }
  
  buff = new AudioFileSourceBuffer(file, 2048); // Bộ đệm 2048 byte
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out); // Bắt đầu phát

  Serial.print("Đang phát: ");
  Serial.println(filePath);
  Serial.printf("Play audio Heap: %d b\n", ESP.getFreeHeap());
}

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
  Serial.println("stop");
  Serial.printf("Heap: %d b\n", ESP.getFreeHeap());
}

void mp3_setup() {
  Serial.begin(115200);
  delay(1000);

  // Khởi động SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("Không thể khởi động SD card!");
    while (1);
  }
  Serial.println("SD card đã sẵn sàng.");

  // Quét thẻ SD để lấy danh sách file MP3
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break; // Không còn file nào
    String name = entry.name();
    if (name.endsWith(".mp3") || name.endsWith(".MP3")) { // Chỉ lấy file MP3
      songs[totalSongs] = String("/") + name; // Thêm "/" vào đầu đường dẫn
      Serial.print(totalSongs);
      Serial.print(": ");
      Serial.println(songs[totalSongs]);
      totalSongs++;
    }
    entry.close();
  }
  root.close();

  if (totalSongs == 0) {
    Serial.println("Không tìm thấy file MP3 nào trên thẻ SD!");
    while (1);
  }


  // Khởi tạo đầu ra âm thanh qua DAC
  out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
  out->SetPinout(0, 0, DAC_PIN);


  // Không phát bài nào ngay, chờ người dùng chọn
}

void chon_nhac_mp3(int songIndex) {
  if (mp3 && mp3->isRunning()) { // Kiểm tra nếu đang phát nhạc
    if (!mp3->loop()) mp3->stop(); // Tiếp tục xử lý hoặc dừng nếu lỗi
  } else {
    // Kiểm tra songIndex hợp lệ
    if (songIndex >= 0 && songIndex < totalSongs) {
      StopPlaying(); // Dừng bài hiện tại (nếu có)
      play(songs[songIndex]); // Phát bài được chọn
    }
  }

    // Nếu bài hát kết thúc, hiển thị lại hướng dẫn
    if (!mp3 || !mp3->isRunning()) {
      Serial.println("Đã phát xong bài hát.");
      delay(1000); 
    }
  }

