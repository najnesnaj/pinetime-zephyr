Starting with some basic applications
=====================================


The best way to get a feel of zephyr for the smartwatch, is to start building applications.


The watch framework is under /app. 

The framework contains a clock, bluetooth, a procedure to upgrade over the air, cts  ...

To reduce the complexity, samples are provided.
Each sample contains a single feature of the framework.

Push the button
***************

- A button for the posix simulation watch, is a lvgl push button.
- A button for the pinetime is a real button, which needs 2 (!) gpio ports
- A button for the Desay D6 is a real button, which needs 1 gpio port.

To complicate matters, a button on the pinetime can be both an lvgl button and a  real gpio-enabled button.

Using a framework, which would suit these watches, needs to distinguish between the boards (use a condition with parameter : CONFIG_BOARD)



posix
*****

Building and Running
--------------------

The "native_posix_64" board is your own linux-box.
This means that you can execute the code on your system.
You do not need a smartwatch.



.. code-block:: console

             west build -p -b native_posix_64 samples/button/sdlbutton 


running : ./build/zephyr/zephyr.exe


pinetime
********

Building and Running
--------------------

.. code-block:: console

             west build -p -b pinetime_devkit1 samples/button/pinebutton 

running : west flash



Reading out the button on the watch
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    The pinetime does have a button on the side. 
    The desay D6 has a touchbutton in front.
    The virtual POSIX watch has a touchbutton    



*Note:*:
`The pinetime watch has a button out port (15) and button in port (13). You have to set the out-port high. Took me a while to figure this out...` 



    


















