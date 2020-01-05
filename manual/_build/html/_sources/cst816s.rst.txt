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
In zephyr is no touchscreen driver yet.
In order to investigate, the touchscreen driver has been created as a sensor.
In fact it senses you finger ;)


Requirements
************


for this sensor does not exist any driver, so here's what I did to create one under zephyr

adapt CMakeLists.txt
--------------------
~/zephyrproject-2/zephyr/drivers/sensor
add_subdirectory_ifdef(CONFIG_CST816S           cst816s)


adapt Kconfig
--------------

~/zephyrproject-2/zephyr/drivers/sensor


add yaml file
-------------
~/zephyrproject-2/zephyr/dts/bindings/sensor
add  hynitron,cst816s.yaml

edit KConfig
------------

source "drivers/sensor/cst816s/Kconfig"

create driver
-------------
see under drivers/sensor/cst816s

complement the pinetime.dts file with the following (under samples/sensor/bma280) 

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


Todo
****


References
**********


