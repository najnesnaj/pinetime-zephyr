# display (st7789)

## Display    example

This is just a simple display test.
It displays coloured squares, but it allows you to check if the screen is OK.

**TIP: While connecting 5V, do not connect 3.3V at the same time**

```
The watch has background leds for the LCD.

They need to be on (LOW) to visualize the display.
Have a look in the source code.
```

```
$  west build -p -b pinetime samples/display/st7789v
```

Once the compilation is completed you can upload the firmware.

If all goes well, you should see some coloured squares on your screen.

**Note : in order to get the display st7789 Picture-Perfect, you might need a zephyr patch**

have a look at : [https://github.com/zephyrproject-rtos/zephyr/pull/20570/files](https://github.com/zephyrproject-rtos/zephyr/pull/20570/files)
You will find them in this repo under patches-zephyr.
