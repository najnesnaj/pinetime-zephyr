zephyr on the pinetime smartwatch
=================================


Blinky    example
~~~~~~~~~~~~~~~~~

**Note: I think you need to connect the 5V, just connecting the SWD cable (3.3V) is likely not enough to light up the leds**


::

    The watch does not contain a led as such, but it has background leds for the LCD. 
    
    Once lit, you can barely see it, cause the screen is black.


.. code-block:: console

     copy the board definition for the pinetime to the zephyrproject directory
     $ cp (this repo)pinetime  ~/zephyrproject/zephyr/boards/arm/pinetime 

     replace the blinky sample with the one in this repo 
     $ cp (this repo)blinky  ~/zephyrproject/zephyr/samples/basic


have a look at the pinetime.dts file, here you see the definition of the background leds.

.. code-block:: console

           gpios = <&gpio0 14 GPIO_INT_ACTIVE_LOW>;
           gpios = <&gpio0 22 GPIO_INT_ACTIVE_LOW>; 
           gpios = <&gpio0 23 GPIO_INT_ACTIVE_LOW>;




`building an image, which can be found under the build directory`


.. code-block:: console

    $ west build -p -b pinetime samples/basic/blinky

once the compilation is completed you can upload the firmware
~/zephyrproject/zephyr/build/zephyr/zephyr.bin 



