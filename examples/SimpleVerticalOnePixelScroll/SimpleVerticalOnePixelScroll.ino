// Does not work! May never work!

/*
   SimpleVerticalOnePixelScroll.ino
   Sketch to demonstrate 1-pixel vertical scrolling on the OLED.
   Created July 30, 2025
*/

#include <SSD1306_I2CPlus.h>
#include <Wire.h>

SSD1306Plus display;

void setup() {
  Wire.begin();
  display.begin(0x3C);

  // Only scroll first page
  display.clear();
  display.setCursor(0, 0);
  display.println("scroll", HIGH);
  display.updateDisplay();
  delay(500);

  // Vertical+horizontal scroll left and up, scroll pages 0-7, 2 frames interval
  display.setupScrollHVOne(LEFT, UP, 0, 7, FRAMES_2);
  display.startScroll();
  delay(2000);
  display.stopScroll();
  delay(500);

  // Vertical+horizontal scroll right and down, scroll pages 0-7, 2 frames interval
  display.setupScrollHVOne(RIGHT, DOWN, 0, 7, FRAMES_2);
  display.startScroll();
  delay(2000);
  display.stopScroll();
  delay(500);

}

void loop() {}
