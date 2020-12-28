# LittlevGL Basic Sample

## Overview

This sample application displays “Hello World” in the center of the screen
and a counter at the bottom which increments every second.

LittlevGL is a free and open-source graphics library providing everything you need to create embedded GUI with easy-to-use graphical elements, beautiful visual effects and low memory footprint.

## Requirements

The program has been modified to light up the background leds.

**TIP: matching label : DISPLAY**

```
Matching labels are necessary!
pinetime.conf:CONFIG_LVGL_DISPLAY_DEV_NAME="DISPLAY"
pinetime.overlay:               label = "DISPLAY"; (spi definition)
```

## Building and Running

```
west build -p -b pinetime samples/gui/lvgl
```

### modifying the font size :

```
west build -t menuconfig
```

goto:

    
    * additional libraries


    * lvgl gui library

    (look for fonts, and adapt according to your need)

### apply changes of the changed config:

```
west build
```

(instead of west build -p (pristine) which wipes out your customisation)

## Todo

> 
> * Create a button


> * touchscreen activation (problem cause zephyr does not support this yet)


> * lvgl supports lv_canvas_rotate(canvas, &imd_dsc, angle, x, y, pivot_x, pivot_y) should be cool for a clock, chrono…

## References

[https://docs.littlevgl.com/en/html/index.html](https://docs.littlevgl.com/en/html/index.html)

LittlevGL Web Page: [https://littlevgl.com/](https://littlevgl.com/)
