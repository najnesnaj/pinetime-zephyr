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


How to install the open source watch framekit
---------------------------------------------

The kit should work alongside the zephyr installation.
Just get a copy of the "app" directory.

.. code-block:: none

   <work>  /app
        ├──/zephyr 
        ├──.....



the app-directory contains the drivers and source code and(!) modified board definitions.




**TIP : sometimes you run into trouble compiling: removing the build directory can help in that case**




