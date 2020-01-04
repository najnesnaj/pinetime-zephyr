# pinetime-zephyr


in this repository you will find a manual, created with sphinx:
::

            -html
            -pdf
            -epub

In the manual is explained how you can create programs (firmware) for the pinetime open source watch.


Once you install zephyr, you only have to copy the board definition file.

You can compile all the samples and try them out.

In this repository you can find modified directories.
You can copy them to the zephyrproject directory.

::
           -pinetime (contains the board definition -> boards/arm)
           -st7789v (samples/display)
           -blinky etc  (samples/.... contains all modified and added samples)

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
   -accel sensor
   -heart rate sensor (and HR detection) 


TODO: 
-----


   -touchscreen
   -powermanagement
   -DFU (wireless firmware update)
   -CTS (setting time in bluetooth) 

