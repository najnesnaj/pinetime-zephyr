# LittlevGL Basic Sample

## Overview

This sample application displays “Hello World” in the center of the screen.

## Requirements


* Desay D6 OLED SSD1306


* Linux box


* Pinetime

## Building and Running

west build -p -b ds_d6 -d build-lvgl samples/lvgl

or

west build -p -b native_posix_64 samples/lvgl

run : ./build/zephyr/zephyr.exe

west build -p -b pinetime_devkit1 samples/lvgl

run : ./build/zephyr/zephyr.exe

## References
