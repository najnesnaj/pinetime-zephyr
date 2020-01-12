# PineTime Zephyr

[PineTime](https://www.pine64.org/pinetime/) firmware toolkit based on [Zephyr Project](https://www.zephyrproject.org/) RTOS.

A collection of drivers, libraries and samples to build your own PineTime smart watch firmware.

## Where To Start?
Read the tutorial! A helpful manual is included in the repository:
 - [pdf](oswatch.pdf)
 - [epub](asmartwatchbasedontheNordicnrf52832microcontroller.epub)
 - [html](manual/_build/html/index.html)

## Installation Overview
1. Follow the Zephyr [Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) to install zephyr SDK and tools.
2. Install `west` meta tool (https://docs.zephyrproject.org/latest/guides/west/install.html).
3. Create a working directory and enter it.
```
mkdir work
cd work
```
3. Use west to clone pinetime repository and initialize pinetime project.
```
west init -m https://github.com/najnesnaj/pinetime-zephyr
```
Alternatively, you can also clone using manifest from specific branch or tag:
```
west init -m https://github.com/<user>/pinetime-zephyr --mr <branch>
```
4. Use `west` to use clone and checkout all dependant repositories specified in `west.yml` (inluding zephyr).
```
west update
```
5. Enjoy!


If you used zephyr and west before and want to stick to the same zephyr copy then you can clone pinetime next to zephyr in working directory and update manifest and west.
```
west config manifest.path pinetime
```

Resources:
- West documentation: https://docs.zephyrproject.org/latest/guides/west
- nRF Connect SDK is using zephyr in similar way and its documentation can be helpful as well: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html

## What Is Included?
In this repository you can find modified directories that need to be copied to the base Zephyr project directory to add support for the PineTime board.

* **pinetime** Contains the board definition -> boards/arm.
* **samples** Added and updated samples for blinky, ST7789V display etc.
* ...

## Project Roadmap
### DONE
- the display
- bluetooth BLE
- graphics libraries
- - LittlevGL
- - Adafruit GFX
- RTC
- Serial NOR flash   
- accel sensor
          - heart rate sensor 

### TODO
- HR detection (algorithm)
- testing accel sensor interrupt
- touchscreen
- powermanagement
- DFU (wireless firmware update)
- CTS (setting time in bluetooth) 
