============================
Zephyr  smartwatch framework
============================


Suppose you want to build a cycle computer quickly.
You need :
- bluetooth 
- a touchscreen
- a button
- time (clock)
- a method of setting the clock
- wireless firmware updating 
- timer functions
- powersaving
- battery management
- several graphical screens, with buttons graphics 


You could start from scratch, or use a framework and only add the stuff you need for your cyclecomputer :
- cadence sensor
- display speed
- record speed



Suppose you have an idea for a portable device, before running to the shop to buy a dev-board, develop hardware ....
You could use the framework as a startingpoint, since it supports a virtual posix-board.




::

    this document started off in setting up zephyr RTOS on the PineTime smartwatch. 
    
    https://wiki.pine64.org/index.php/PineTime
   
    It evolved to accomodate other nordic nrf52832 based watches (Desay D6....) and a Virtual watch (native_posix_64)

    Zephyr allows for hardware abstraction. The framework is not limited to Nordic nrf52. 
    In theory : compiling with a different board definition file should be enough. (minor changes might be necessary - see the button sample)


    The virtual watch lets you create and debug software without a watch nor a debugprobe. (=cheap)
    There exist a lot of cheap (chinese) watches based on Nordic microcontrollers.
    The hardware will probably differ, but with minor adjustments it should be possible to adapt the framework.


::

    the approach in this manual is to get quick results :
        - minimal effort install
        - try out the samples 
        - inspire you to modify and enhance


    The masterpiece is the firmware toolkit.
    Since it is a big chunk of code, you might be lost.
    
    The samples in the /app directory, contain parts of the toolkit.
    Like building blocks, which form the final firmware.



    



    
suggestion : 
	- follow the Zephyr installation instructions 
        - try some examples

	- if you like it copy the /app directory for some more fun
       



.. image:: ./PineTime-830x400.png






