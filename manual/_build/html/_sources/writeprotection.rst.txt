.. _flashing:

Howto flash your zephyr image 
=============================


Once you completed your ``west build`` , your image is located under the build directory


.. code-block:: console

    $ cd ~/zephyrproject/zephyr/build/zephyr
    here you can find zephyr.bin which you can flash 


I have an orange pi (single board computer) in my network.

I copy the image using $scp -P 8888 zephyr.bin 192.168.0.77:/usr/src/pinetime
(secure copy using my user defined port 8888 which is normally port 22)


.. Note::

         the PineTime watch is read/write protected
         executing the following : nrf52.dap apreg 1 0x0c shows 0x0

         Mind you st-link does not allow you to execute that command, you need J-link.
         There is a workaround using the GPIO of a raspberry pi or a Orangepi.
         You have to reconfigure Openocd with the --enable-cmsis-dap option.

         Unlock the chip by executing the command:
         > nrf52.dap apreg 1 0x04 0x01
