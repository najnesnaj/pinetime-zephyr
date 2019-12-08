===================================
scanning the I2C_1 port
===================================
::

    The pinetime does not have a serial port. 
    I do not have a segger debugging probe. 
    A way around this, it to put a value in memory at a fixed location.
    With openocd you can peek at this memory location.

Building and Running
********************

In this repo under samples you will find an adapted i2c scanner program.


.. code-block:: console

             west build -p -b pinetime samples/drivers/i2c_scanner


    
.. note::

         #define MY_REGISTER (\*(volatile uint8_t\*)0x2000F000)


         in the program you can set values:
         MY_REGISTER=1;
         MY_REGISTER=8;

         this way you know till where the code executes

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
      0x2000f000: 00c24418

*Note:*:

this corresponds to 0x18, 0x44 and 0xC2 (which is endvalue of scanner, so it does not detect touchscreen, which should be touched first....)

  











