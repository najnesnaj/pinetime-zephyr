# Install zephyr

## update on 31-12-2020

Pinetime has become part of the standard zephyr distribution!
This manual was initially created with Pinetime as an external application.
As from today you can install zephyr and execute a pinetime sample!

However the drivers for the Heartrate sensor, accell sensor and touch screen are not - yet - part of the standard zephyr-distribution.
These drivers are work in progress.

```
west build -p -b pinetime_devkit0 samples/boards/pine64_pinetime
```

A second and important sample is provided.
Zephyr and the LVGL graphics library play together, using the touchscreen.
The standard Focaltech touchscreen driver has been adapted slightly, as well as the board definition files.
To get the sample up and running copy both the adapted board definition files and touchscreen driver, replacing the standard zephyr ones.

```
west build -p -b pinetime_devkit0 samples/display/lvgl
```

The focaltech touchscreen driver is more recent/better than the cst816s touchscreendriver.
Still, there is room for improvement (slide events …..)

The battery driver was provided as a module and is not working yet.

The accel sensor bma421 driver is working, and work has been done to distill a stepcounter out of it.

The heartrate sensor hrs3300, could work, but is kind of useless without a proper algorith (open source) to distill a heartbeat out of it.
You can stil play around with it’s capabilities as a lightsensor / led device.

## In case you already have zephyr installed:

Pinetime works as external (out of tree) application.
You can clone pinetime next to zephyr in the working directory and update manifest and west.

```
west config manifest.path pinetime
```

## In case you start from scratch :

[https://docs.zephyrproject.org/latest/getting_started/index.html](https://docs.zephyrproject.org/latest/getting_started/index.html)

the documentation describes an installation process under Ubuntu/macOS/Windows

I picked Debian (which is not listed)
…. and soon afterwards ran into trouble

this behaviour is known as : stuborn or stupid, but I remain convinced it could work

In the Zephyr getting started page :


1. select and update OS


2. install dependencies


3. Get the source code

```
instead of following the procedure:
       cd ~
       west init zephyrproject
       cd zephyrproject
       west update

you should do this :
        cd ~
        mkdir work
        cd work
        west init -m https://github.com/najnesnaj/pinetime-zephyr
        west update
```


1. complete the other steps

to test if your install works :

cd ~/work/pinetime

west build -p -b pinetime samples/basic/blinky

**TIP : sometimes you run into trouble compiling: removing the build directory can help in that case**
