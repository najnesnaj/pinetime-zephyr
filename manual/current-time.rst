Current Time Service 
=================
https://www.bluetooth.com/specifications/gatt/services/
https://www.bluetooth.com/specifications/gatt/characteristics/
0x1805 current time service
0x2A2B current time characteristic

Requirements:
~~~~~~~~~~~~
You need : 
           - a CTS server (use of bluez on linux explained)
                                      - start the CTS service (python script)
                                      - connect to the CTS client
           - a CTS client (the pinetime watch)


BLE Peripheral CTS sample for zephyr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example demonstrates the basic usage of the current time service.
It is based on the https://github.com/Dejvino/pinetime-hermes-firmware.
It starts advertising it's UUID, and you can connect to it.
Once connected, it will read the time from your CTS server (bluez on linux running the gatt-cts-server script in my case)



first build the image


.. code-block:: console


        $  west build -p -b pinetime samples/bluetooth/peripheral-cts



Using bluez on linux to connect
~~~~~~~~~~~~~~~~~~~~~~~~~~
The pinetime zephyr sample behaves as a peripheral: 
                          - first of all start the cts service
                           -connect to the pinetime with bluetoothctl
    
Using bluetoothctl:
.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on


    [NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
    once you see your device
    [blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)



Howto use Bluez on linux to set up a time service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Within the bluez source distribution there is an example GATT (Generic Attribute Profile)server. It advertises some standard service such as heart rate, battery ...
Koen zandberg adapted this script, so it advertises the current time :
https://github.com/bosmoment/gatt-cts/blob/master/gatt-cts-server.py


You might have to install extra packages:

.. code-block:: console
		apt-get install python-dbus 
 		apt-get install python-gi 
		apt-get install python-gobject

  
