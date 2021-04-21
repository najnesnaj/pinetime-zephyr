.. _pinebutton-sample:

Pinetime  Button  Sample
########################

Overview
********

The button on the pinetime uses 2(!) GPIO ports.

This sample application displays "a LED";
Long Press on the button and the LED changes "color" 
Short Press toggles the LED.


Several messages are printed to the serial port.
In order to view these you will need a segger JLink probe (RTT).


Requirements
************

pinetime
segger jlink debugprobe

Building and Running
********************

west build -p -b pintime_devkit1  samples/button/pinebutton


References
**********


.. _LittlevGL Web Page: https://littlevgl.com/
