.. _oswatch:

OSWatch Framework 
#################

Overview
********


This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on pinetime and on the ds_d6 oled watch.



Requirements
************

no requirements since it can run without board (simulation)

Building and Running
********************


west build -p -b  native-posix_64 oswatch


References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
.. _SDL2: https://www.libsdl.org
