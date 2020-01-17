zephyr on the pinetime smartwatch
=================================


Blinky    example
~~~~~~~~~~~~~~~~~

**Note: I think you need to connect the 5V, just connecting the SWD cable (3.3V) is likely not enough to light up the leds**


::

    The watch does not contain a led as such, but it has background leds for the LCD. 
    
    Once lit, you can barely see it, cause the screen is black.






have a look at the pinetime.dts file, here you see the definition of the background leds.

.. code-block:: console
           $ vi  ~/work/pinetime/boards/arm/pinetime 

           gpios = <&gpio0 14 GPIO_INT_ACTIVE_LOW>;
           gpios = <&gpio0 22 GPIO_INT_ACTIVE_LOW>; 
           gpios = <&gpio0 23 GPIO_INT_ACTIVE_LOW>;




`building an image, which can be found under the build directory`


.. code-block:: console

    $ cd ~/work/pinetime
    $ west build -p -b pinetime samples/basic/blinky

once the compilation is completed you can upload the firmware
~/work/pinetime/build/zephyr/zephyr.bin 



