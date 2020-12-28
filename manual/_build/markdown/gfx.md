# GFX Library Sample

## Overview

This sample is built on top of the ST7789 display sample (display (st7789)), extending it with the [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library).
The library was ported from Arduino and has the same functionality and API.
See `src/main.cpp` for examples on the GFX API usage.

See display (st7789) for more details on working with the display itself.

## Usage

Add the gfx sample from this repo into your project:

```
$ cp samples/gui/gfx ~/zephyrproject/zephyr/samples/gui/
```

**NOTE**: In order to make the library work the sample is built with C++ support. This is achieved by having the following line in the sample’s prj.conf configuration:

`CONFIG_CPLUSPLUS=y`

Build & flash the sample:

```
$  west build -p -b pinetime samples/gui/gfx
$  west flash
```

If all goes well, you should see a looping graphical test: drawing lines, rectangles, triangles etc.
