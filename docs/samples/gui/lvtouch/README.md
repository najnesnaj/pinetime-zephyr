# Touchscreen Basic Sample

## Overview

This sample application displays touchscreen-values x and y in the center of the screen.

The touchscreen triggers an interrupt when touched.
This means that data is ready and can be collected.

However, using the interrupt with the handler, does not seem to work within the GUI.
When used in samples/sensor/cst816s, it runs....

## Requirements

Pinetime watch
zephyr cst816s driver

## Building and Running

west build -p -b pinetime samples/gui/lvtouch

## References
