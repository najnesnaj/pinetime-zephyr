========================
Install zephyr 
========================


update on 31-12-2020
--------------------


Pinetime has become part of the standard zephyr distribution!

These days you can install zephyr and execute a pinetime sample!


::

	west build -p -b pinetime_devkit0 samples/boards/pine64_pinetime




How to install zephyr
---------------------


https://docs.zephyrproject.org/latest/getting_started/index.html

the documentation describes an installation process under Ubuntu/macOS/Windows


How to install the open source watch frame kit
----------------------------------------------

The kit should work alongside the zephyr installation.
Just get a copy of the "app" directory.

.. code-block:: none

   <work>  /app
        ├──/zephyr 
        ├──.....



the app-directory contains the drivers and source code and(!) modified board definitions.

Linux rules
-----------

The development has been done on a virtual linux machine.
For testing bluetooth functionality, I have used linux as well. 
In this manual you'll find a procedure to communicate to the device from a linux box.
Updating the firmware wireless? Possible from a linux box!

Suppose you want to measure how many steps employees do a day?
You could readout everything using a linux box, and handle the data using all the available tools of the box.




**TIP : sometimes you run into trouble compiling: removing the build directory can help in that case**




