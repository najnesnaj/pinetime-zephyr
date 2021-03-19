bluetooth (BLE) 
===============




Bluetooth is a very nice feature, it lets you exchange data wirelessly and (!) update firmware wirelessly.


The PineTime uses a Nordic nrf52832 chip, which has BLE functionality build into it.

To test, you can compile a standard application : Eddy Stone.


A word on bluetooth-serial commnunication
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Smartwatch manufacterers usually supply you with a smartwatch app.
This app can communicatie trough bluetooth, and get/send data to the watch.

Unfortunately this is not a standard Zephyr feature!

You could use nRF Connect SDK (often referred as NCS),it is Nordic Semiconductor SDK based on zephyr. It has additional features that could be useful for pinetime, namely bluetooth modules and bluetooth services. Important to mention that even though, NCS forks zephyr it is kept close to it and it is regularly updated to latest zephyr (typically every 2-3 weeks).

NCS has no impact on build framework and overall user experience. The only downside I can think of is that NCS is based on older version of zephyr (~2 weeks behind).

The main reason why i'm bringing it up is bluetooth shell. Zephyr has very nice shell module with multiple transports (UART, RTT). NCS extends it with bluetooth transport (using Nordic Uart Service) and host tool for using it. There is an application for linux from which you can use shell over bluetooth, get logs, etc.. It is really cool and can be very useful when playing with pinetime where you can get logs or control/tune things with only wireless connection to your PC. Here is a demonstration of bluetooth console used in one of nordic reference kits: https://www.youtube.com/watch?v=3KzTfr6S4pg&t= . It's based on nRF5 SDK (not zephyr) but bluetooth shell (and PC tool) was taken from there.

The Nordic UART Service (NUS) shell transport sample demonstrates how to use the receive shell commands from a remote device.

NCS is using BSD-5-Clause-Nordic license (https://github.com/NordicPlayground/fw-nrfconnect-nrf/blob/master/LICENSE)

Zephyr RTOS and the samples I use/create use the Apache License 2.0.
A permissive license whose main conditions require preservation of copyright and license notices. Contributors provide an express grant of patent rights. Licensed works, modifications, and larger works may be distributed under different terms and without source code.


Eddy Stone
~~~~~~~~~~

 see:   :ref:`bluetooth-eddystone-sample`


**Note:**  compile the provided example, so a build directory gets created 


.. code-block:: console

    $ west build -p -b pinetime_devkit0 samples/bluetooth/eddystone 

``this builds an image, which can be found under the build directory``

Using the created bluetooth sample:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


I use linux with a bluetoothadapter 4.0.
You need to install bluez.

.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on

And your Eddy Stone should be visible.
     




It is the peripheral which advertises, and the central that reads the data.

A sample which advertises a heartrate :

::

        west build -p -b pinetime_devkit0 samples/bluetooth/peripheral_hr

you could use your smartphone or bluez on linux to read out the heartrate.

Or if you have another watch, the central will connect to the peripheral and read out the heartrate. 

::

        west build -p -b pinetime_devkit0 samples/bluetooth/central_hr


the no-bluetooth, no-watch approach : nrf52_bsim 
------------------------------------------------

Suppose you have no watch, no devboard, nor any bluetooth dongles?
You can still test your bluetooth enabled application.
https://docs.zephyrproject.org/latest/boards/posix/nrf52_bsim/doc/index.html

We follow the same logic, but this time we specify the nrf52_bsim board.

::

	west build -p -b nrf52_bsim samples/bluetooth/peripheral_hr
	west build -p -b nrf52_bsim samples/bluetooth/central_hr
	cp build/zephyr/zephyr.exe  ${BSIM_OUT_PATH}/bin/bs_nrf52_bsim_samples_bluetooth_central_hr


Once compiled you can execute both the peripheral and central firmware, and(!) you have to start the bluetooth simulation.
By starting each application in its own terminal, you can keep an eye on the output.


::

	${BSIM_OUT_PATH}/bin/bs_nrf52_bsim_samples_bluetooth_central_hr -s=trial_sim -d=1 
	
	 zephyr/build/zephyr/zephyr.exe -s=trial_sim -d=0 
         ${BSIM_OUT_PATH}/bin/bs_2G4_phy_v1 -s=trial_sim -D=2 -sim_length=10e6 




the no-watch approach : simulation on a laptop 
----------------------------------------------

how to activate bluetooth?

VBOX running ubuntu (first disactivate driver in windows)
(CTRL home -- select usb -- (intel in my case)) -- this lets you select the integrated bluetoothmodule of your laptop

::

	 hciconfig hci0 down

	 west build -p -b native_posix_64 samples/bluetooth/peripheral_hr
	 ./build/zephyr/zephyr.exe --bt-dev=hci0


Now you can connect your smartphone to the posix_64 bluetooth device!
 
Or, with a second bluetooth interface (eg dongle)
.. code-block:: console

        bluetoothctl
	[bluetooth]# devices
	Device C6:78:40:29:EC:31 Zephyr Heartrate Sensor
	Device C9:16:85:ED:B6:4E DS-D6 b64e
        Device C8:B7:89:A9:B0:C9 Espruino-107 b0c9
	Device 00:1A:7D:DA:71:0B posix_64


	[bluetooth]# info 00:1A:7D:DA:71:0B
        Device 00:1A:7D:DA:71:0B (public)
	Name: posix_64
	Alias: posix_64
	Paired: no
	Trusted: no
	Blocked: no
	Connected: no
	LegacyPairing: no
	UUID: Device Information        (0000180a-0000-1000-8000-00805f9b34fb)
	UUID: Current Time Service      (00001805-0000-1000-8000-00805f9b34fb)



If you have a smartphone, you can download the nrf utilities app from nordic.


Bluez
~~~~~



With Bluez on linux you can investigate the bluetoothservices,  using bluetoothctl:



.. code-block:: console

    #bluetoothctl
    [bluetooth]#scan on


    [NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
    once you see your device
    [blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)

    then you can already see the services



using bluez to write something to the device
--------------------------------------------

Characteristic
	/org/bluez/hci0/dev_74_71_4B_D5_18_21/service001f/char0023
	00002a38-0000-1000-8000-00805f9b34fb
	Body Sensor Location

.. code-block:: console

	[dsd6]# select-attribute /org/bluez/hci0/dev_74_71_4B_D5_18_21/service001f/char0023
	write <data=0x1>


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
      
