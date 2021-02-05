Battery 
#######


the samples just gets an analog reading from the battery



.. code-block:: console

      west build -p -b pinetime samples/sensor/battery 




Overview
********


The battery level is measured on port 31, trough an ADC conversion.

voltage = (value * 6)/1024
percentage remaining  ((voltage - 3.55)*100)*3.9; 

A module should be able to report battery status in millivolts and charge level in percentage. Additionally, it should notify when external power is connected and when battery is being charged.
Module will use adc (saadc peripheral) to measure battery voltage and gpio driver to monitor charge indication pin (pin 0.12) and power presence pin (0.19).
Battery voltage can be in range from 3.0V - 4.2V (?). Unfortunately, internal reference (0.6V) can only be used for voltages up to 3.6V (due to minimal gain of 1/6). VDD/4 reference can be used with 1/6 gain to measure voltages up to 4.95V. Test is needed to check how accurate is VDD as reference.
Discharge curve (https://forum.pine64.org/showthread.php?tid=8147) will be used to calculate charge level in percent.
Things to consider:
saadc periodical calibration (spec suggests calibration if temperature changes by 10'C)
inaccuracy of results: oversampling? never report higher level than before (if charge not connected), etc.


Todo
****
check pin when charging

References
**********

https://forum.pine64.org/showthread.php?tid=8147
