# LittlevGL Basic Sample

## Overview

This sample application displays “Hello World” in the center of the screen
and a counter at the bottom which increments every second.

When touched in the center (it is a button) a counter is displayed at the top.
The counting stops if button is pressed again.

## Requirements

a pinetime or similar watch

## Building and Running

west build -p -b pinetime_devkit0 samples/display/lvgl
