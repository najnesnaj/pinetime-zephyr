.. _flashing:

howto flash your zephyr image 
=============================


Once you completed your ``west build`` , your image is located under the build directory


.. code-block:: console

    $ cd ~/work/pinetime/zephyr/build/zephyr
    here you can find zephyr.bin which you can flash 
    
    


 I use Openocd to flash.
 Just connect : telnet 127.0.0.1 4444
 
 .. code-block:: console
 
     program zephyr.bin

howto remove the write protection 
=================================

::
         the PineTime watch is read/write protected (at least the one I got)
         executing the following : nrf52.dap apreg 1 0x0c shows 0x0

         Mind you st-link does not allow you to execute that command, you need J-link.
         
         There is a workaround using the GPIO of a raspberry pi or a Orangepi.
         You have to reconfigure Openocd with the --enable-cmsis-dap option.

         Unlock the chip by executing the command:
         > nrf52.dap apreg 1 0x04 0x01
