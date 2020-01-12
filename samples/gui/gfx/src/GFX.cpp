#include "GFX.h"
#include "Adafruit-GFX-Library/Adafruit_GFX.h"

GFX::GFX(struct device* display_dev, int16_t w, int16_t h) : Adafruit_GFX(w,h) {
	this->display_dev = display_dev;
        this->pixelBufferDesc.pitch = 1;
        this->pixelBufferDesc.width = 1;
        this->pixelBufferDesc.height = 1;
};

void GFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	u8_t b[2];
	b[0] = (color >> 8);
	b[1] = (color >> 0);
	display_write(display_dev, x, y, &this->pixelBufferDesc, &b);
}

void GFX::startWrite() {}

void GFX::writePixel(int16_t x, int16_t y, uint16_t color) {
  drawPixel(x, y, color);
}

void GFX::writeFastVLine(int16_t x, int16_t y, int16_t h,
                                  uint16_t color) {
  writeFillRect(x, y, 1, h, color);
}

void GFX::writeFastHLine(int16_t x, int16_t y, int16_t w,
                                  uint16_t color) {
  writeFillRect(x, y, w, 1, color);
}

void GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 uint16_t color) {
  u8_t b[2 * w * h];
  struct display_buffer_descriptor d;
  d.pitch = w;
  d.width = w;
  d.height = h;
  // TODO: optimize
  for (int i = 0; i < w * h; i++) {
    b[i * 2 + 0] = color >> 8;
    b[i * 2 + 1] = color >> 0;
  }
  display_write(display_dev, x, y, &d, &b);
}

void GFX::endWrite() {}

/**
 * GFX Factory
 */
GFX* createGFX(struct device* display_dev)
{
	struct display_capabilities capabilities;
	display_get_capabilities(display_dev, &capabilities);

	int sw = capabilities.x_resolution; 
	int sh = capabilities.y_resolution; 

	return new GFX(display_dev, sw, sh);
}


