.. _rtc:

Real Time Clock
###############

Overview
********

This sample application "clock" uses the RTC0 timer.
It uses the counter driver.


It will serve as a building block for a "time of the day" clock.

In addition it will need a function to set the time.

In bluetooth one can use CTS (central time service)

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


see : :ref:`clock-sample`


Building and Running
********************



.. code-block:: console

       west build -p -b pinetime samples/gui/clock


Todo
****

    - time of day clock
    - setting the time


References
**********

