.. _testirq:

Touchscreen IRQ
###############

Overview
********

The touchscreen generates an interrupt when touched.

Requirements
************

A counter that keeps track of the number of times touched.

This value is stored at a fixed location in memory, because I have a simple test setup.


Building and Running
********************


.. zephyr-app-commands::
   samples/basic/testirq
