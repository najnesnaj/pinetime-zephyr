# LittlevGL Basic Sample

## Overview

This sample application displays a buttton on top of the screen
and a counter at the bottom which increments every second.

The KSCAN input driver is defined in the board-definition.

## Requirements

this is a posix sample - so no dev board necessary

## Building and Running

west build -p -b native_posix_64 samples/display/lvgl -DCONF=board/native-posix_64

## References
