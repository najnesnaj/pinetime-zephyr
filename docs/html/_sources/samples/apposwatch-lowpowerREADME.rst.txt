.. _oswatch:

Lowpower oswatch 
################

Overview
********

After a few seconds the watch switches to lowpower.
Long press a button and it wakes-up.

The simulated watch behaves differently and while sleeping, a message is displayed.


Which Power is saved?
*********************

There are two procedure power on and power off.
Right now only the display is controlled from these procedures.
If additional power needs to be saved, one can add extra lowpower features (switching of sensors ....)


Button clicking
***************

Each time the button is clicked, there is a check for lowpower mode (consequently a startup is executed)

This method can be done differently (eg using an interrupt from the accel-sensor)

Building and Running
********************

::

	 west build -p -b native_posix_64 oswatch-lowpower
	 ./build/zephyr/zephyr.exe --bt-dev=hci0

