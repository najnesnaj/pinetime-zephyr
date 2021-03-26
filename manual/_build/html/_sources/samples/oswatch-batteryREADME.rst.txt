.. _oswatch:

Battery OSWatch Framework 
#########################

Todo    
********
Not functional yet...  
WIP (work in progress)

Overview
********


This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on pinetime and on the ds_d6 oled watch.


This frame can be used if you need power management (PM).

The application keeps track of the battery, and is frugal on energy.



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
