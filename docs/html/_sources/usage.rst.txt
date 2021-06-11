============================
Howto use the framework ?
============================

Boards
------

This framework is build around 3 watches : 
	- desay D6
	- pinetime
	- simulated X86

Each of these watches has its own board definition file.

While using the framework for a different setup, you will need a specific board definition file.
This can easily be created, modifying an existing one.



Complexity
----------

As you add more features, the complexity and(!) code increases.

An incremental approach has been used : from simple to more complex.

	- oswatch
	- oswatch-cts
	- oswatch-bt
	- oswatch-calendar
	- oswatch-lowpower
	- oswatch-battery
	- oswatch-fota

(each extends the functionality of the previous one)

Samples
---------

As the firmware can be a bit overwhelming, a sample directory is provided.
These samples can be installed and tested.
Their purpose is to clarify certain functionality. 
Suppose you want to know how to use bluetooth notification, you can compile/install/use the smaller sample.

Bluetooth
---------
	( oswatch-cts )
	( oswatch-bt )

I have used Bluez on linux, and python scripts to communicate with the watch.

Maybe there are other ways (android), but you would probably need to write apps or are limited to the functionality of existing apps.

The python scripts can easily be extended and provide a good way to automate the communication process (eg when you need to communicate with multiple watches or in case of the internet of things)


Power saving
------------
	( oswatch-battery )

Power saving makes sense when the device is battery operated, which is probably not always the case.



Updating over the air
---------------------
	( oswatch-fota )

Firmware updating over the air in zephyr should be failsafe.
As a consequence you need space for 2 images. 1 working and 1 updating.
If the update process fails, you can carry on.

The space can be a challenge if you do not have extra flash memory. (512 / 2 = 256)
































