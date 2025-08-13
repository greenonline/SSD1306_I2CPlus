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
  //stopScroll();         // <----- Not needed every call. 
                          // Just call once (before calling this method)
                          // Either after a continuous scroll, 
                          // or to ensure continuous scroll is stopped
   
  sendCommand(0x2C + int(dir));
  sendCommand(0x00);
  sendCommand(start);
  sendCommand(interval);
  sendCommand(end);
  sendCommand(0x00);
  sendCommand(0xFF);
}

// dir: 0 - right, 1 - left
void SSD1306Plus::setupScrollHVOne(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval) {
  //stopScroll();         // <----- Not needed every call. 
                          // Just call once (before calling this method)
                          // Either after a continuous scroll, 
                          // or to ensure continuous scroll is stopped

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

void SSD1306Plus::setupScrollHOneWait(bool dir, uint8_t start, uint8_t end, uint8_t interval, int scrollWaitTime) {
  setupScrollHOne(dir, start, end, interval);
  delay(scrollWaitTime);
}

void SSD1306Plus::setupScrollHVOneWait(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval, int scrollWaitTime) {
  setupScrollHVOne(dirX, dirY, start, end, interval);
  delay(scrollWaitTime);
}


// New commands to v1.5

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

void SSD1306Plus::zoom(void){
  sendCommand(0xD6);
  sendCommand(0x01);
}

void SSD1306Plus::setZoom(bool i){
  sendCommand(0xD6);
  sendCommand(i);
}

void SSD1306Plus::stopZoom(void){
  sendCommand(0xD6);
  sendCommand(0x00);
}

// Extra bonus features!
// COM Pins configuration
void SSD1306Plus::setCOMPins(bool com, bool lr){
  sendCommand(0xDA);
  sendCommand(0x02 + com*32 + lr*64);
}

void SSD1306Plus::setCOMPins_SEQCOM_NOLR(void){
  sendCommand(0xDA);
  sendCommand(0x02);
}

void SSD1306Plus::setCOMPins_ALTCOM_NOLR(void){
  sendCommand(0xDA);
  sendCommand(0x12);
}

void SSD1306Plus::setCOMPins_SEQCOM_ENLR(void){
  sendCommand(0xDA);
  sendCommand(0x22);
}

void SSD1306Plus::setCOMPins_ALTCOM_ENLR(void){
  sendCommand(0xDA);
  sendCommand(0x32);
}

// Charge Pump
void SSD1306Plus::setChargePump(bool i){
  sendCommand(0x8D);
  sendCommand(0x10+4*i);
}

void SSD1306Plus::setChargePumpOn(void){
  sendCommand(0x8D);
  sendCommand(0x14);
}

void SSD1306Plus::setChargePumpOff(void){
  sendCommand(0x8D);
  sendCommand(0x10);
}

void SSD1306Plus::setChargePumpDisplay(bool i){
  sendCommand(0x8D);
  sendCommand(0x10+4*i);
  sendCommand(0xAF);
}

void SSD1306Plus::setChargePumpOnDisplay(void){
  sendCommand(0x8D);
  sendCommand(0x14);
  sendCommand(0xAF);
}

void SSD1306Plus::setChargePumpOffDisplay(void){
  sendCommand(0x8D);
  sendCommand(0x10);
  sendCommand(0xAF);
}

