Battery 
#######


the samples just gets an analog reading from the battery


there is a sample in this repository which can be copied to the zephyr samples directory

.. code-block:: console

      west build -p -b pinetime samples/sensor/battery 




Overview
********


The battery level is measured on port 31, trough an ADC conversion.

voltage = (value * 6)/1024
percentage remaining  ((voltage - 3.55)*100)*3.9; 


Todo
****
check pin when charging

References
**********

https://forum.pine64.org/showthread.php?tid=8147
