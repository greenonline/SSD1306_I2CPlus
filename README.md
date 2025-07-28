# SSD1306_I2CPlus
A library that inherits and extends the SSD1306_I2C Arduino library with undocumented 1-pixel scroll, zoom, fade and blink commands.

The `SSD1306_I2C` library can be found here, [SSD1306 OLED Display with Arduino][1] - [direct download][2]

## The new commands

### Undocumented commands

The 1-pixel scroll commands (`2Ch` and `2Dh`) are not documented in either the [v1.1][3] nor [v1.5][4] versions of the data sheet. However, they are mentioned in [this answer](https://stackoverflow.com/a/69200268/4424636) to [Scroll long text on OLED display][7] on Stack Overflow:

> The SSD1306 chip provides commands to enable both continuous scrolling and 1 pixel scroll. For our purpose of scrolling long text, the continuous scroll is not useful, as we want to scroll exactly one pixel. Therefore, we need to use the 1 pixel scroll command. The commands take the same parameters, except for the first opcode byte. For some reason in the widely circulated (and pretty old) datasheet online, the 1 pixel scroll command is missing, but it is there in HW.
> 
>     #define CMD_CONTINUOUS_SCROLL_H_RIGHT		0x26
>     #define CMD_CONTINUOUS_SCROLL_H_LEFT		0x27
>     #define CMD_ONE_COLUMN_SCROLL_H_RIGHT		0x2C
>     #define CMD_ONE_COLUMN_SCROLL_H_LEFT		0x2D
> 
> Use the latter two.

### Commands from v1.5 of the datasheet

There are two commands, that are missing from the commonly distributed v1.1 data sheet, documented in v1.5 of the data sheet:

 - Fade/Blink (`23h`)
 - Zoom (`D6h`).

## Links

### Datasheets
- [v1.1][3]
- [v1.5][4]


### Stack Exchange

 - [SSD1306 - Is there a way to scroll a certain number of pixels only?][5]
 - [Adafruit SSD1306 scrolling function][6]
 - [Scroll long text on OLED display][7]

  [1]: https://www.aidansun.com/articles/ssd1306-arduino/
  [2]: https://www.aidansun.com/dl/SSD1306_I2C.zip
  [3]: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
  [4]: https://www.rlocman.ru/i/File/2020/04/17/SSD1306.pdf
  [5]: https://arduino.stackexchange.com/q/51420/6936
  [6]: https://electronics.stackexchange.com/q/485198/64015
  [7]: https://stackoverflow.com/q/40564050/4424636

