Starting with some basic applications
=====================================


The best way to get a feel of zephyr for the PineTime watch, is to start building applications.

The gpio ports, i2c communication, memory layout, stuff that is particular for the watch is defined in the board definition file.

The provided samples are standard zephyr application, with some minor modifications.




Blinky    example
~~~~~~~~~~~~~~~~~



::

    The watch does not contain a led as such, but it has background leds for the LCD. 
    
    Once lit, you can barely see it, cause the screen-LCD remains black.

    The screen contains three leds, this way the intensity is set.






have a look at the pinetime.dts file, here you see the definition of the background leds.

.. code-block:: console
           $ vi  ~/work/pinetime/boards/arm/pinetime 

           gpios = <&gpio0 14 GPIO_INT_ACTIVE_LOW>;
           gpios = <&gpio0 22 GPIO_INT_ACTIVE_LOW>; 
           gpios = <&gpio0 23 GPIO_INT_ACTIVE_LOW>;




`building an image, which can be found under the build directory`

see : :ref:`blinky-sample` 

.. code-block:: console

    $ cd ~/work/pinetime
    $ west build -p -b pinetime samples/basic/blinky

once the compilation is completed,  you can find the firmware under :
~/work/pinetime/build/zephyr/zephyr.bin 



Reading out the button on the watch
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    The pinetime does have a button on the side. 
    
    In order to check if the button is pressed, it set a value in memory.
    With openocd you can peek at this memory location.

Building and Running
********************

see : :ref:`button-sample` 

*Note:*:
`The watch has a button out port (15) and buttin in port (13). You have to set the out-port high. Took me a while to figure this out...` 

.. code-block:: console

             west build -p -b pinetime samples/basic/button


    
.. note::

         #define MY_REGISTER (\*(volatile uint8_t\*)0x2000F000)


         in the program you can set values:
         MY_REGISTER=(read button value);

         this way you know till whether the code executes


a way to set port 15 high (hard-coded of course :))

.. code-block:: console

         gpio_pin_configure(gpiob, 15,GPIO_DIR_OUT); //push button out
         gpio_pin_write(gpiob, 15, &button_out); //set port high





.. code-block:: console

      #telnet 127.0.0.1 4444

Peeking

.. code-block:: console

      once your telnet sessions started:
      Trying 127.0.0.1...
      Connected to 127.0.0.1.
      Escape character is '^]'.
      Open On-Chip Debugger
      >mdw 0x2000F000 0x1
      0x2000f000: 00000100 (switch pushed)














