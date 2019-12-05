# pinetime-zephyr


in this repository you will find a manual, created with sphinx:
            -html
            -pdf
            -epub

In the manual is explained how you can create programs (firmware) for the pinetime open source watch.


Once you install zephyr, you only have to copy the board definition file.

You can compile all the samples and try them out.

In this repository you can find modified directories, which you can copy to the zephyrproject directory
           -pinetime (board definition -> boards/arm)
           -st7789v (samples/display)
           -blinky (samples/basic)

IMPORTANT:
----------
in order to work properly you need to install a zephyr patch : 
https://github.com/zephyrproject-rtos/zephyr/pull/20570/files



ALREADY DONE:
-------------

   -the display
   -bluetooth BLE
   -graphics library (LittlevGL)
   -RTC
   -Serial NOR flash   


TODO: 
-----

   -touchscreen
   -accel sensor
   -powermanagement
   -DFU (wireless firmware update)
   -heart rate sensor (and HR detection) 
   -CTS (setting time in bluetooth) 

