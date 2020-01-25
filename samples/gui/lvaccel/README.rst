.. _lvaccel-sample:

Display accel values
####################

Overview
********

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second.

It display the values x,y,z from the bosch BMA421 accel sensor.


Requirements
************

Pinetime watch
definitions can be found under the boards sub-directory
         - pinetime.conf
         - pinetime.overlay

Building and Running
********************

west build -p -b pinetime samples/gui/lvgl


References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
