=========
debugging  
=========

Segger JLink
------------

::  

        The pinetime smartwatch does not have a serial port.
        A way around this is to use a Segger Jlink debug-probe and enable logging and shell over RTT:
        
        in prj.cfg:

	CONFIG_LOG=y
	CONFIG_USE_SEGGER_RTT=y
	CONFIG_SHELL=y
	CONFIG_SHELL_BACKEND_RTT=y

	start the debugger : 
	west debug
        and enter : continue
	
	This starts up in the background "Segger Jlink Processes"
 
    
    
.. note::

       What happens when you type : west debug?
       You could type this on the command prompt.


.. code-block:: console

        (this start the server)
	JLinkGDBServer -select usb -port 2331 -if swd -speed 4000 -device nRF52832_xxAA -silent -singlerun
	(this starts the debug session)
	~/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb /root/zephyrproject/app/build/zephyr/zephyr.elf -ex target :2331 -ex halt -ex reset -ex load
	telnet 127.0.0.1 19021 (putty on linux) start the rtt console and shows the debug-log


Black Magic
------------

::

    The ds-D6 smartwatch has a serial port. 


    The blackmagicprobe can lauch a debugger : west debug --runnerblackmagicprobe.
    The probe has a serial port /dev/ttyACM1 (linux : minicom -b 115200 -D /dev/ttyACM1)




STM32 - Raspberry - OpenOCD
---------------------------


::

    If you do not have a Segger debug probe nor a serial port, you can put a value in memory at a fixed location.
    With openocd you can peek at this memory location.
    If you own a raspberry pi or an orange pi, you can use the GPIO header.
    Another cheap option is an stm32 debug probe.


    
.. note::

         #define MY_REGISTER (\*(volatile uint8_t\*)0x2000F000)


         in the program you can set values:
         MY_REGISTER=1;
         MY_REGISTER=8;

         this way you know till where the code executes

.. code-block:: console

      #telnet 127.0.0.1 4444

programming

.. code-block:: console

      once your telnet sessions started:
      Trying 127.0.0.1...
      Connected to 127.0.0.1.
      Escape character is '^]'.
      Open On-Chip Debugger
      >mdw 0x2000F000 0x1
      
      the last byte shows the value of your program trace value











