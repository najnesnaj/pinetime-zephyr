# PineTime Zephyr

[PineTime](https://www.pine64.org/pinetime/) firmware toolkit based on [Zephyr Project](https://www.zephyrproject.org/) RTOS.

A collection of drivers, libraries and samples to build your own PineTime smart watch firmware.






## A Word of warning ......

It's the first time I accepted "merge pull requests"

The last one messed everything up.

I work on this project on my free time.

I simply do not have enough time to debug.

So if you want to use this project, ignore the latest commit...

Simply copying the board definition and samples into an existing install, will get you going.












## Where To Start?
Read the tutorial! A helpful manual is included in the repository:
 - [pdf](oswatch.pdf)
 - [epub](asmartwatchbasedontheNordicnrf52832microcontroller.epub)
 - [html](manual/_build/html/index.html)

## Installation Overview
1. Follow the Zephyr [Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) install `west` meta tool (https://docs.zephyrproject.org/latest/guides/west/install.html).
2. Create a top level directory and enter it.
```
mkdir pinetime
cd pinetime
```
3. Clone this repository
```
git clone https://github.com/<user>/pinetime-zephyr.git pinetime
```
4. Init `west` to use pinetime manifest
```
west init -l pinetime
```
5. Fetch all repositories
```
west update
```
6. Enjoy!

See the manual above for more details.

If you used zephyr and west before then you can clone pinetime to top level
directory and edit west configuration file (`<top level dir>/.west/config`) to
point to pinetime and call `west update`.

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
