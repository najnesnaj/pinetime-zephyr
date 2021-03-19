# display

## Display   Types

There are three types of display included.


* a st7789 color display used in the pinetime


* a monochrome SSD1306 OLED display used in the desay D6


* a on-screen display SDL simulated on linux

### Several methods of using the display

Included in the zephyr distribution are :
- the Little Graphics Library  (LVGL)
- Character framebuffer (cfb)

For the pinetime the LVGL library might be a good option, since it has a big screen, colors and (!) is touch sensitive.

For the DS-D6 which has a monochrome OLED small display, the character framebuffer could be the best option.

### The human eye

You can print something to the serial port, use the Segger RTT, but having a sample which displays something on the screen is the equivalent of blinking a LED.

Instead of the blinky blinking the LED, most samples include the screen.
