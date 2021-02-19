.. _lvgl-sample:

LittlevGL Basic Sample
######################

Overview
********

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second.

LittlevGL is a free and open-source graphics library providing everything you need to create embedded GUI with easy-to-use graphical elements, beautiful visual effects and low memory footprint. 



Simulation
**********

In order to avoid uploading to check what the display looks like, there is a simple way to simulate this.
I've tested this on Ubuntu 18.04 64bit. You'll need the SDL2 library.


.. code-block:: console

	west build -p -b native_posix_64 samples/display/lvgl -DCONF=board/native-posix_64


after the building, you can find build/zephyr/zephyr.exe (and execute this to see display-layout)


the sample is provided as samples/display/lvgl-posix


Requirements
************


The program has been modified to light up the background leds.


**TIP: matching label : DISPLAY**
:: 

        Matching labels are necessary!
        pinetime.conf:CONFIG_LVGL_DISPLAY_DEV_NAME="DISPLAY"
        pinetime.overlay:               label = "DISPLAY"; (spi definition)

Building and Running
********************


.. code-block:: console

       west build -p -b pinetime samples/lvgl

modifying the font size :
-------------------------

.. code-block:: console

      west build -t menuconfig


goto:
    - additional libraries 
    - lvgl gui library

    (look for fonts, and adapt according to your need)

apply changes of the changed config:
------------------------------------


.. code-block:: console

      west build 

(instead of west build -p (pristine) which wipes out your customisation)




References
**********
https://docs.littlevgl.com/en/html/index.html

LittlevGL Web Page: https://littlevgl.com/
