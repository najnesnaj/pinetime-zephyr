Touchscreen
###########

In my first release I created a touchscreendriver that read the x-y coordinates from the pinetime screen.

Meanwhile a rudimentary touchscreen driver exist in Zephyr. (KSCAN_TOUCH)

It integrates with LVGL.

I managed to adapt the driver from Focaltech, so it now supports the Pinetime as well.

However it is not capable of detecting events like "slide up/down", but point and click is usable.

       



Overview
********
Touchscreen Hynitron

.. code-block:: console
      git clone https://github.com/lupyuen/hynitron_i2c_cst0xxse




Requirements
************



Building and Running
********************


Todo
****
      -support more touchscreen events

References
**********







