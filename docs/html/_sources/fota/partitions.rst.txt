
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

The flash-layout can be modified so as 1 chunk is on system flash and 1 chunk is on SPI NOR flash.
This way the space for your firmware remains almost the same.

.. code-block:: console


	chosen {
		zephyr,flash = &flash0;
		//zephyr,flash = &flash1;
		zephyr,code-partition = &slot0_partition;
	};


        Rename the SPI JEDEC NOR Flash definition to : flash1

        flash1: mx25r6435f@1 {
		compatible = "jedec,spi-nor";
		reg = <1>;
		spi-max-frequency = <80000000>;
		label = "MX25R64";
		jedec-id = [0b 40 16];
		size = <67108864>;
		has-be32k;
 		erase-block-size = <4096>;
		write-block-size = <4>;
	};

         
         
         
         &flash0 {
         	/*
         	 * For more information, see:
         	 * http://docs.zephyrproject.org/latest/guides/dts/index.html#flash-partitions
         	 */
         	partitions {
         		compatible = "fixed-partitions";
         		#address-cells = <1>;
         		#size-cells = <1>;
         
         		boot_partition: partition@0 {
         			label = "mcuboot";
         			reg = <0x00000000 0xc000>;
         		};
         		slot0_partition: partition@c000 {
         			label = "image-0";

                        change the size of partition 0 from 0x32000 to 0x64000

         			reg = <0x0000C000 0x64000>;
         		};

                        move slot1 partition to &flash1
                        
         		//slot1_partition: partition@3e000 {
         		//	label = "image-1";
         		//	reg = <0x0003e000 0x32000>;
         		//};
         		scratch_partition: partition@70000 {
         			label = "image-scratch";
         			reg = <0x00070000 0xa000>;
         		};
         		storage_partition: partition@7a000 {
         			label = "storage";
         			reg = <0x0007a000 0x00006000>;
         		};
         	};
         };

         &flash1 {
         	partitions {
         		compatible = "fixed-partitions";
         		#address-cells = <1>;
         		#size-cells = <1>;
         		slot1_partition: partition@3e000 {
         			label = "image-1";
         			reg = <0x00000000 0x64000>;
         		};
         	};
         };
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
