/*
   SSD_1306Plus.h - Library for controlling a 128x64 SSD1306 OLED
   Created July 28, 2025
   MIT License
*/

#ifndef SSD1306_I2CPLUS_H
#define SSD1306_I2CPLUS_H

#include <Arduino.h>
#include <SSD1306_I2C.h>

// Constants
#define FRAMES_2   0b111
#define FRAMES_3   0b100
#define FRAMES_4   0b101
#define FRAMES_5   0b000
#define FRAMES_25  0b110
#define FRAMES_64  0b001
#define FRAMES_128 0b010
#define FRAMES_256 0b011

#define OUTLINE false
#define FILL    true

#define RIGHT false
#define LEFT  true

#define UP   false
#define DOWN true

class SSD1306Plus : public SSD1306 {
  uint8_t _displayBuf[1024]; // Display buffer
  uint8_t _addr;             // I2C address
  uint8_t _curX     = 0;
  uint8_t _curY     = 0;
  uint8_t _curFront = 0;
  uint8_t _textSize = 1;

  void _drawCircleBase(int x0, int y0, int x, int y, bool color, bool fill);

  void _newLine();

public:

  // Scrolling
  void setupScrollHOne(bool dir, uint8_t start, uint8_t end, uint8_t interval);
  void setupScrollHVOne(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval);

  void setupScrollHOneWait(bool dir, uint8_t start, uint8_t end, uint8_t interval, int scrollWaitTime);
  void setupScrollHVOneWait(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval, int scrollWaitTime);


  // New features from v1.5 datasheet
  void fade(uint8_t time);
  void blink(uint8_t time);
  void stopFadeBlink(void);
  void stopFade(void);
  void stopBlink(void);
  void setZoom(bool i);

};
#endif
