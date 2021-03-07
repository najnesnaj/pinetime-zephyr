# Open Source Watch toolkit for the  Zephyr RTOS

originally a  
[PineTime](https://www.pine64.org/pinetime/) firmware toolkit based on [Zephyr Project](https://www.zephyrproject.org/) RTOS.

now evolved into a framework which has the potential to support other watches, cyclecomputers, wearables ...

Included in this toolkit is a virtual watch, which you can run on your computer. (no real watch, devboard, debugprobe is needed!)


## Contributing to this project

The pinetime board (watch) has become a part of the zephyr distribution.

You can contribute to this project, by adding your own board definition file, better coding, suggestions ...


## Where To Start?
Read the tutorial! A helpful manual is included in the repository:
 - [pdf](oswatch.pdf)
 - [epub](opensourcewatch.epub)
 - [html](https://najnesnaj.github.io/pinetime-zephyr/html)
 - [md](https://najnesnaj.github.io/pinetime-zephyr/)

## Installation Overview
1. Follow the Zephyr [Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) to install zephyr SDK and tools.
2. Install `west` meta tool (https://docs.zephyrproject.org/latest/guides/west/install.html).


build your first sample!

 - west build -p -b pinetime_devkit0 samples/boards/pine64_pinetime


## Major update on 18/02/2021

The initial toolkit was focused on getting zephyr up and running on the pinetime smartwatch.

Zephyr is still under development and some nifty features were added since (or I discovered them only lately)

 - touchscreen support (kscan)
 - out of tree development
 - virtual board
 - ssd1306 oled spi support

it inspired me to morph the original pinetime-toolkit into an open-source-watch-framework.

## philosophy

Quick&easy, open and cheap!

Once you set up zephyr on your system, you only have to copy the "app" directory alongside.
There is an extensive "hands-on" manual included, it is an addition of the zephyr manual.

Although dev-boards are not expensive, you might just want to try things out, without spending money.
Bluetooth, LVGL, board definition, touchscreen can be run native on X86.
Another advantage : no need for a debug probe.
You can get a taste of debugging your firmware with gdb.
I've included compiled firmware, which you can run on your linux(64)  box.

I used a osbox virtual linux ubuntu 18, so you do not even have to own a computer.

## The Movie

I made a demo clip : oswatchclip.mp4
File should be on github, not sure if it will work...

### Copy
suppose you already have ../work/zephyr installed,

copy /app to ../work
### Build 
west build -p -b native_posix_64 oswatch
### Run 
./build/zephyr/zephyr.exe
### Result 
a simulated watch is displayed on the screen
### Bluetooth
the simulated watch can use bluetooth! (some extra config is needed : this is explained in the included manual) 


Resources:
- West documentation: https://docs.zephyrproject.org/latest/guides/west


## What Is Included?
In this repository you can find files that supplement a zephyr installation.

* **board definition** Contains the board definition for the pinetime, ds_d6, and native_posix_64
* **drivers** Contains the drivers for the pinetime, ds_d6
* **samples** These are building blocks, which eventually end up in the oswatch-firmware. 

## Project Roadmap
### DONE
- the display
- bluetooth BLE
- graphics libraries
- - LittlevGL
- RTC
- Serial NOR flash
- accel sensor
- heart rate sensor
- touchscreen (not with all the gizmo's yet)
- CTS (setting time in bluetooth)
- DFU (wireless firmware update)
- serial port

### TODO
- build-in features of bosch accel sensor (eg step counter)
- powermanagement
- watchdog
- touchscreen (out of tree)

### NICE TO HAVE 
- HR detection (algorithm)
- cycle computer

#### Other watches 

There are quite a few hackable watches, based on the same nrf52832 microcontroller.
I have also made a repository for the desay D6, which is a ssd1306 OLED based, cheap chinese watch with a serial port.
[other smartwatches](https://github.com/najnesnaj/dsd6-zephyr)
This watch combined with a "blue-pill" black magic debug probe, which contains a serial port, might be one of the cheapest zephyr dev boards available!


