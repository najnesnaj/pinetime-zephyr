Menuconfig 
==========


board and shield
~~~~~~~~~~~~~~~~


The PineTime smart watch is one single unit.
Howeven from a hardware point of perspective, one could consider it as a microcontroller with a shield.

The microcontroller is defined in the board (-b pintime) definition.

The display can be considered as a shield on top op the board.

In this repository, have a look under board/shields.

You will find an overlay and a configuration file.

You can copy these under ~zephyrproject/zephyr.


It is then located in a central directory, and you can build the image using:



.. code-block:: console

       west build -p -b pinetime samples/gui/lvgl -- -DSHIELD=pinetime






 
