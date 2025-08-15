## Important Notes

### 1-pixel scroll

#### 1-pixel scrolling and `stopscroll()` 

Note that, unlike the continuous scroll methods of the parent class `SSD1306_I2C`, the 1-pixel scroll methods do not call `stopScroll()` at the beginning of the methods, as it is not required, nor efficient, to do so, for the 1-pixel scroll methods *only*. 

However, it *is* good practice to call `stopScroll()` *once* before commencing a series of 1-pixel scroll method calls – or any scroll commmands for that matter – just to be certain that any continuous scrolling, that *might* be occurring, is halted – otherwise the display's RAM buffer may become corrupted.

#### Use of 'interval' byte for 1-pixel scroll

The 'interval' byte, `C[2:0]`, as detailed in the datasheet on page 31, Table 9-1 section 2, obviously has no meaning for a 1-pixel scroll.

Setting the 'interval' byte to `0b111` (i.e. `FRAMES_2`) prevents wrap-around scrolling and instead causes a white "background" to appear, from the edge of the screen, when scrolling. Setting to `0b000` (i.e. `FRAMES_5`) eliminates this white background effect, and enables wrap-around scrolling. 

#### Waiting for the 1-pixel scroll

I found, on the Seeeduino Xiao (SAMD21) at least, that a delay ***is*** required, *immediately* after issuing a 1-pixel scroll command, or when ***repeatedly*** issuing 1-pixel scroll commands. 

```none
    display.setupScrollHOne(LEFT,  0, 7, FRAMES_5);
    delay(wait_time);
```

Without any `delay(wait_time)` then no scrolling occurred at all. If `wait_time` is less than 12 ms delay, then that causes some of the scrolls to fail, and the full 50 pixels are *not* scrolled. The closer that the delay is to zero, the less distance, in pixels scrolled, the text/images actually move. The minimum length of the required delay probably depends upon the frequency of the µController, so you may need to experiment for your particular setup.

### Pairing of 1-pixel scroll and delay

Seeing as a *brief* delay is *always* required, after a 1-pixel scroll, it seemed expedient to combine the two together in wrapper methods that just combine the two into one simple call:

```none
void SSD1306Plus::setupScrollHOneWait(bool dir, uint8_t start, uint8_t end, int interval); 
void SSD1306Plus::setupScrollHVOneWait(bool dirX, bool dirY, uint8_t start, uint8_t end, uint8_t interval, int scrollWaitTime);
```

### Vertical 1-pixel scroll

Feel free to experiment! You can try to find the *mythical* 1-pixel vertical scroll yourself by changing the values of the command byte in `setupScrollHVOne` in `SSD1306_I2CPlus.cpp`.

### Do this BEFORE commencing display

Be sure to stop scroll, fade, blink, and especially zoom, at the beginning of a sketch, as the SSD1306 may has a previous configuration in RAM that needs to be cleared:

```none
  // Stop scroll, fade, blink and zoom
  display.stopFadeBlink();
  display.stopScroll();
  display.stopZoom();
```

Zoom can be left configured from a previous sketch, leading to confusing results. This occurs if the display is in zoom mode, whilst the new sketch is being uploaded.

