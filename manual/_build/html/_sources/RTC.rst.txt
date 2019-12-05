.. _rtc:

Real Time Clock
###############

Overview
********

This sample application "clock" uses the RTC0 timer.
It uses the counter driver.


Requirements
************


Make sure the prj.conf contains the following : 

:: 

        CONFIG_COUNTER=y



You need the Kconfig file, which contains :

::

        config COUNTER_RTC0
                bool
                default y if SOC_FAMILY_NRF



Building and Running
********************

copy the samples/gui/clock from this repository to the zephyr one.


.. code-block:: console

       west build -p -b pinetime samples/gui/clock


Todo
****

    - time of day clock
    - setting the time


References
**********

