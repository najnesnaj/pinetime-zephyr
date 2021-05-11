.. _oswatch:

Setting up an alarm/calendar event  
###################################

Overview
********



This sample sets up a calendar event.

Time and date (calendar event) are read from a gatt-server.

Once the event is due, the watch blinks the screen and vibrates. 


Requirements
************

A bluetooth gatt-server. (this is supplied : using bluez on linux)

Included is a python-script : gatt-calendar-server.py, for use with bluez on linux.

::

    python3 gatt-calendar-server.py

you need to connect to the watch in order, to have it read the time.

::

	bluetoothctl
	scan on (gets you list of bluetoothdevices)
	connect D5:A0:A2:6D:A0:D5 (pick the pinetime - macaddress) 


Building and Running
********************


west build -p -b  pinetime_devkit1 oswatch-calendar


References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
.. _SDL2: https://www.libsdl.org
