.. _lvgl-sample:

LittlevGL Basic Sample
######################

Overview
********

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second. 


If an input driver is supported, such as the touch panel controller on the pinetime  
boards, "Hello World" is enclosed in a button that changes to the toggled state
when touched.

Requirements
************

a pinetime or similar watch

Building and Running
********************

.. note::
   When deferred logging is enabled you will likely need to increase
   :option:`CONFIG_LOG_STRDUP_BUF_COUNT` and/or
   :option:`CONFIG_LOG_STRDUP_MAX_STRING` to make sure no messages are lost or
   truncated.

Example building for :ref:`nrf52840dk_nrf52840`:

.. zephyr-app-commands::
   :zephyr-app: samples/gui/lvgl
   :board: nrf52840dk_nrf52840
   :shield: adafruit_2_8_tft_touch_v2
   :goals: build flash

Example building for :ref:`native_posix`:

.. zephyr-app-commands::
   :zephyr-app: samples/gui/lvgl
   :board: native_posix
   :goals: build flash

References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
.. _SDL2: https://www.libsdl.org
