.. _oswatch:

OSWatch bluetooth setting parameters 
####################################



Overview
********


This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on the pinetime and on the ds_d6 oled watch.


Bluetooth
*********

This application adds bluetoothfunctionality to update 6 parameters.
One should be able to read out and set these parameters.


Requirements
************

no requirements since it can run without board (simulation)

Building and Running
********************


west build -p -b  native-posix_64 oswatch-bt


References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
.. _SDL2: https://www.libsdl.org
