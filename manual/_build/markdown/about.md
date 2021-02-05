# About

I got a pinetime development kit very early.
I would like to thank the folks from [https://www.pine64.org/](https://www.pine64.org/) for the kit.

The Nordic nrf52832 is an Arm based, 32bit microcontroller with a lot of flash, RAM memory and(!) bluetooth!
It is a good platform to explore the wonderfull world of opensource RTOS's.
I choose the Zephyr platform, because it already contained the display driver, and the bluetooth functionality.
Furthermore it can be updated wirelessly.

I started of with adapting simple samples, so they would run on the pinetime watch.
Meanwhile I learned how to adapt the board definition file.
Gradually this morphed into a pinetime-toolkit.
A few experts contributed and improved this kit so it became usable.

I took a long break from this project, zephyr evolved and a project for creating an open source watch, the hypnos firmware flourished.

The drivers for the heartrate sensor, touchpanel that I adapted, became obsolete.
The pinetime board definition file is now part of the zephyr RTOS distribution.

Recently I discovered that the standard focaltech touchscreen driver could be adapted easily so it would run on the pinetime and integrate nicely with the LVGL-gui. There were several OLED ssd1306 watches on my desk and I wondered if I could run Zephyr and LVGL (graphical stuff) on them as well. (yes, we can!)
I played around with the "native_posix_64" board, which is a virtual board that allows you to run firmware on your computer instead of on the watch (no need for flashing).

This gave me the idea for an opensource-watch-framework.

```
A word of warning: this is work in progress.
You're likely to have a better skillset then me.
You are invited to add the missing pieces and to improve what's already there.
```
