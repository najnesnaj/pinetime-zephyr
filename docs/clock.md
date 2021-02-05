# LittlevGL Clock Sample

see : LittlevGL Clock Sample

## Overview

This sample application displays a "clockbackground" in the center of the screen.

LittlevGL is a free and open-source graphics library providing everything you need to create embedded GUI with easy-to-use graphical elements, beautiful visual effects and low memory footprint.



![image](clockback.png)

## Requirements

Make sure the prj.conf contains the following :

```
CONFIG_LVGL=y
CONFIG_LVGL_OBJ_IMAGE=y
```

LitlevGL uses a "c" file to store the image.
You need to convert a jpg, or png image to this c file.
There is an online tool : [https://littlevgl.com/image-to-c-array](https://littlevgl.com/image-to-c-array)

## Building and Running

```
west build -p -b pinetime samples/gui/clock
```

## Todo

> 
> * create an internal clock (and adjustment mechanism, eg. bluetooth cts)


> * lvgl supports lv_canvas_rotate(canvas, &imd_dsc, angle, x, y, pivot_x, pivot_y) should be cool for a clock, chrono...

## References

[https://docs.littlevgl.com/en/html/index.html](https://docs.littlevgl.com/en/html/index.html)

LittlevGL Web Page: [https://littlevgl.com/](https://littlevgl.com/)
