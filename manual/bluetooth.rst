bluetooth (BLE) example 
=======================


Eddy Stone
~~~~~~~~~~

**Note:**  compile the provided example, so a build directory gets created 


.. code-block:: console

    $ west build -p -b pinetime samples/bluetooth/eddystone 

``this builds an image, which can be found under the build directory``


I use linux with a bluetoothadapter 4.0.
You need bluez.

.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on

And your Eddy Stone should be visible.
     

If you have a smartphone, you can download the nrf utilities app from nordic.


Ble Peripheral
~~~~~~~~~~~~~~~

this example is a demo of the services under bluetooth

first build the image


.. code-block:: console


        $  west build -p -b pinetime samples/bluetooth/peripheral -D CONF_FILE="prj.conf" 


the image, can be found under the build directory, and has to be flashed to the pinetime

with linux you can have a look using bluetoothctl



.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on


    [NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
    once you see your device
    [blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)

    then you can already see the services


same thing with the app from nordic, you could try to connect and display value of e.g. heart rate


using Python to read out bluetoothservices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this repo you will find a python script : readbat.py
In order to use it you need bluez on linux and the python `bluepy` module.

It can be used in conjunction with the peripheral bluetooth demo.
It just reads out the battery level, and prints it.


::

     import binascii
     from bluepy.btle import UUID, Peripheral
      
     temp_uuid = UUID(0x2A19)
       
     p = Peripheral("60:7C:9E:92:50:C1", "random")
        
     try:
        ch = p.getCharacteristics(uuid=temp_uuid)[0]
        print binascii.b2a_hex(ch.read())
     finally:
         p.disconnect()
      
