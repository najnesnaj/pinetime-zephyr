Current Time Service 
====================

https://www.bluetooth.com/specifications/gatt/services/

https://www.bluetooth.com/specifications/gatt/characteristics/

- 0x1805 current time service

- 0x2A2B current time characteristic

Requirements:
~~~~~~~~~~~~~~

You need : 
           - a CTS server (use of bluez on linux explained, and android!)
                                      - start the CTS service (python script: gatt-cts-server.py provided)

                                      - connect to the CTS client
           - a CTS client (the oswatch)


BLE Peripheral CTS sample for zephyr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example demonstrates the basic usage of the current time service.
It is based on the https://github.com/Dejvino/pinetime-hermes-firmware.

It starts advertising it's UUID, and you can connect to it.
Once connected, it will read the time from your CTS server 
(bluez on linux running the gatt-cts-server script in my case)



first build the image


.. code-block:: console


        $  west build -p -b pinetime_devkit1 oswatch-cts
	



Using bluez on linux to connect
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The pinetime zephyr sample behaves as a peripheral: 

.. code-block:: console


                          - make sure your linuxbox has bluez running (type bluetoothctl if you're not sure)
                          - first of all start the cts service : python gatt-cts-server.py
                          - connect to the pinetime with bluetoothctl
    
Using bluetoothctl:

.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on


    [NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
    once you see your device
    [blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)



Howto use Bluez on linux to set up a time service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Within the bluez source distribution there is an example GATT (Generic Attribute Profile)server. It advertises some standard service such as heart rate, battery ...
Koen zandberg adapted this script, so it advertises the current time :
https://github.com/bosmoment/gatt-cts/blob/master/gatt-cts-server.py


You might have to install extra packages:

.. code-block:: console

		apt-get install python-dbus 
 		apt-get install python-gi 
		apt-get install python-gobject


Howto use Android to set up a time service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As soon as a device is bonded, Pinetime will look for a CTS server (Current Time Service) on the connected device.
Here is how to do it with an Android smartphone running NRFConnect: 


Start NRFConnect and create a CTS server : Tap the hamburger button on the top left and select "Configure GATT server".

Tap "Add service" on the bottom Select server configuration "Current Time Service"  (0x1805)

Here is for a manual time setup : add the Current Time 0x2A2B characteristic :
in the intial value field add 0x141505130B0D which corresponds to (2021 year 05 month 19 day 11hours 13 minutes)

A device called "PineTime" or "DSD6", or whichever name you gave it,  should appear.

Tap the button "Connect" next to the PineTime device. 

Disconnect and the newly set time should appear.

  
