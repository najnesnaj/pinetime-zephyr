.. _lvgl-sample:

LittlevGL Basic Sample
######################

Overview
********

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second.

Requirements
************

definitions can be found under the boards sub-directory
         - pinetime.conf
         - pinetime.overlay

The program has been modified to light up the background leds.
Might be unnecessary...
can be found in this repo

:: 
        Matching labels are necessary!
        pinetime.conf:CONFIG_LVGL_DISPLAY_DEV_NAME="DISPLAY"
        pinetime.overlay:               label = "DISPLAY"; (spi definition)

Building and Running
********************

Make sure you copied the board definitions.

.. code-block:: console

       west build -p -b pinetime samples/gui/lvgl

modifying the font size :

west build -t menuconfig
goto additional libraries / lvgl gui library
(look for fonts, and adapt according to your need)


west build 


References
**********


LittlevGL Web Page: https://littlevgl.com/
