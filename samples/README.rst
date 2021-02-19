.. _hrs3300:

HRS3300 Heart Rate Sensor
##########################

Overview
********

A sensor application that demonstrates how to poll data from the hrs3300 heart
rate sensor.

Building and Running
********************

This project configures the hrs3300 sensor on the :ref:`pinetime_devkit1` board to
enable the green LED and measure the reflected light with a photodiode. The raw
ADC data prints to the console. Further processing (not included in this
sample) is required to extract a heart rate signal from the light measurement.

.. zephyr-app-commands::
   :zephyr-app: samples/hrs3300
   :board: pinetime_devkit1 
   :goals: build
   :compact:

Sample Output
=============

for this you will need a Segger JLink Console


.. code-block:: console
 
   rtt:~$ sensor get HRS3300 18 (ir -- this switches off the sensor)
   rtt:~$ sensor get HRS3300 19 (red -- this switches on the sensor)
   rtt:~$ sensor get HRS3300 20 (green -- get a value)


   
