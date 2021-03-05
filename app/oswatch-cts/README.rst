.. _oswatch:

Current Time Setting  OSWatch Framework 
#######################################

Overview
********


This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on pinetime and on the ds_d6 oled watch.

This sample reads/sets the time, using bluetooth CTS.


Requirements
************

A bluetooth CTS server.
This can be a smartphone.

Included is a python-script : gatt-cts-server.py, for use with bluez on linux.

::

    python3 gatt-cts-server.py

you need to connect to the watch in order, to have it read the time.

::

	bluetoothctl
	scan on (gets you list of bluetoothdevices)
	connect D5:A0:A2:6D:A0:D5 (pick the pinetime - macaddress) 


Building and Running
********************


west build -p -b  native-posix_64 oswatch-bt


References
**********

.. target-notes::

.. _LittlevGL Web Page: https://littlevgl.com/
.. _SDL2: https://www.libsdl.org
