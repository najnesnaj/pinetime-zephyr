Touchscreen Hynitron
####################


.. code-block:: console

       
      git clone https://github.com/lupyuen/hynitron_i2c_cst0xxse



Overview
********


this does not exist yet in zephyr, but there is work in progress
https://github.com/zephyrproject-rtos/zephyr/pull/16119



Requirements
************

complement the pinetime.dts file with the following (under samples/sensor/bma280) 

.. code-block:: console

     &i2c1 {
             touch@18 {
     	               };
            };
                                                                                                                                                                                                        
Create a file: `/dts/bindings/sensor/touch.yaml`.
Which contains:

::

     compatible: "touch"
     include: i2c-device.yaml
     properties:
            int1-gpios:
            type: phandle-array
            required: false



Building and Running
********************


Todo
****
      -create touchscreen driver
      -create sample

References
**********







