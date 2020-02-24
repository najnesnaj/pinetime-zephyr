
.. _signing:

Partitions
##########


.. code-block:: console


      have a look at boards/arm/pinetime/pinetime.dts


Defining partitions for MCUboot 
-------------------------------


The first step required for Zephyr is making sure your board has flash
partitions defined in its device tree. These partitions are:

- `boot_partition`: for MCUboot itself
- `image_0_primary_partition`: the primary slot of Image 0
- `image_0_secondary_partition`: the secondary slot of Image 0
- `scratch_partition`: the scratch slot


The flash partitions are defined in the pinetime boards folder, in a
file named `boards/arm/pinetime/pinetime.dts`. 


Using NOR flash in partitions 
-----------------------------


The flash space on the Nordic nrf52 is 512K.
Basically with the partitioning you end up with less space for your program.


As the pinetime has an extra spi nor flash chip, we can use this.

The flashlay-out can be modified so as 1 chunk is on system flash and 1 chunk is on SPI NOR flash.
This way the space for your firmware remains almost the same.



















