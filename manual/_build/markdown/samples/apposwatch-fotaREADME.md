# FOTA OSWatch Framework

## Todo

This is not functional yet

## Overview

This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on pinetime and on the ds_d6 oled watch.

This is a demo, when you want to implement firmware updates over the air.

Zephyr has a procedure in place.

Look for MCUBOOT definitions in the source code

## Requirements

no requirements since it can run without board (simulation)

## Building and Running

west build -p -b  native-posix_64 oswatch-fota

## References
