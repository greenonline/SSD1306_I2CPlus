/*
   SSD_1306Plus.cpp - Library for controlling a 128x64 SSD1306 OLED
   Created July 28, 2025
   MIT License
*/

#include <Arduino.h>
#include <Wire.h>

#include "SSD1306_I2CPlus.h"
#include "font.h"

void SSD1306Plus::_drawCircleBase(int x0, int y0, int x, int y, bool color, bool fill) {
  if (fill) {
    int x1Coords[] = { x0 + x, x0 + x, x0 + y, x0 + y };
    int y1Coords[] = { y0 + y, y0 - y, y0 + x, y0 - x };
    int x2Coords[] = { x0 - x, x0 - x, x0 - y, x0 - y };
    int y2Coords[] = { y0 + y, y0 - y, y0 + x, y0 - x };

    for (int i = 0; i < 4; i++) drawLine(x1Coords[i], y1Coords[i], x2Coords[i], y2Coords[i], color);
  } else {
    int xCoords[] = { x0 + x, x0 - x, x0 + x, x0 - x, x0 + y, x0 - y, x0 + y, x0 - y };
    int yCoords[] = { y0 + y, y0 + y, y0 - y, y0 - y, y0 + x, y0 + x, y0 - x, y0 - x };

    for (int i = 0; i < 8; i++) drawPixel(xCoords[i], yCoords[i], color);
  }
}

void SSD1306Plus::_newLine() {
  setCursor(_curFront, _curY + _textSize * 8); // Change cursor position to new line
}



// Scrolling

// dir: 0 - right, 1 - left
void SSD1306Plus::setupScrollHOne(bool dir, uint8_t start, uint8_t end, uint8_t interval) {
  stopScroll();
  sendCommand(0x2C + int(dir));
  sendCommand(0x00);
  sendCommand(start);
  sendCommand(interval);
  sendCommand(end);
  sendCommand(0x00);
  sendCommand(0xFF);
}

// dir: 0 - right, 1 - left
void SSD1306::setupScrollHVOne(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval) {
  stopScroll();

  // Command values for horizontal and vertical
  uint8_t addrs[] = { 0x24, 0x25 };
  uint8_t dirs[]  = { 1, 63 };

  sendCommand(addrs[dirX]);
  sendCommand(0x00);
  sendCommand(start);
  sendCommand(interval);
  sendCommand(end);
  sendCommand(dirs[dirY]);
}

// New commands to v1.5

#define SSD1306_SFB_FADE  0x20
#define SSD1306_SFB_BLINK 0x30

void SSD1306Plus::fade(uint8_t time){
  sendCommand(0x23);
  sendCommand(SSD1306_SFB_FADE + time);
}

void SSD1306Plus::blink(uint8_t time){
  sendCommand(0x23);
  sendCommand(SSD1306_SFB_BLINK + time);
}

void SSD1306Plus::stopFadeBlink(void){
  sendCommand(0x23);
  sendCommand(0x00);
}

void SSD1306Plus::stopFade(void){
  stopFadeBlink();
}

void SSD1306Plus::stopBlink(void){
  stopFadeBlink();
}

void SSD1306Plus::setZoom(bool i){
  sendCommand(0xD6);
  sendCommand(i);
}

