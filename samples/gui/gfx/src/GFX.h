#include <zephyr.h>
#include <device.h>
#include <display.h>

#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00

#include "Adafruit-GFX-Library/Adafruit_GFX.h"

/**
 * Implementation of Adafruit_GFX graphics library for ST7789V display on Zephyr.
 */
class GFX : public Adafruit_GFX {

public:
  GFX(struct device* display_dev, int16_t w, int16_t h); // Constructor

  // This MUST be defined by the subclass:
  void drawPixel(
      int16_t x, int16_t y,
      uint16_t color); ///< Virtual drawPixel() function to draw to the
                           ///< screen/framebuffer/etc, must be overridden in
                           ///< subclass. @param x X coordinate.  @param y Y
                           ///< coordinate. @param color 16-bit pixel color.
  virtual void startWrite(void);
  virtual void writePixel(int16_t x, int16_t y, uint16_t color);
  virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                             uint16_t color);
  virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void endWrite(void);


private:
	struct device *display_dev;
	struct display_buffer_descriptor pixelBufferDesc;
        
};

/**
 * GFX Factory
 */
GFX* createGFX(struct device* display_dev);


