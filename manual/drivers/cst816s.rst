HYNITRON CST816S 
################


this driver does not exist, so it has been created.
Still work in progress ....


there is a sample in this repository which can be copied to the zephyr samples directory

.. code-block:: console

      west build -p -b pinetime samples/sensor/cst816s 




Overview
********


the Hynitron cst816s is a touchscreen.
In zephyr doesn't handle touchscreens yet.
In order to investigate, the touchscreen driver has been created as a sensor.
In fact it senses your finger ;)


Requirements
************


for this sensor does not exist any driver, so here's what I did to create one under zephyr

adapt CMakeLists.txt
adapt Kconfig
add yaml file

create driver
-------------

The driver reads only one position.
Multitouch is possible, but the screen is small....




see under drivers/sensor/cst816s

have a look at the pinetime.dts (under board/arm/pinetime) file:

.. code-block:: console

     &i2c1 {
             cst816s@15 {
                 	compatible = "hynitron,cst816s"; 
     	        	reg = <0x15>;
     	 	        label = "CST816S";
     	                };
            };
                                                                                                                                                                                                        



Building and Running
********************

There are two samples : 
           - samples/gui/lvtouch (graphical)
           - samples/sensor/cst816s (no graphics)




           
Todo
****

The graphical sample doesn't handle interrupts.

References
**********

There is little available for this touchscreen.






