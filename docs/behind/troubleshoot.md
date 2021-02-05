# Troubleshooting drivers

Drivers, like the one for the accel sensor BMA421 or the touchscreen CST816S, can deal with interrupts.

Adapting existing drivers did not get me the desired quick results.

Even after analyzing the behaviour, setting values at each function step, did not get me any further.

## Overview

The drivers can use interrupts.

In the settings/config one can choose between OWN_THREAD and GLOBAL_THREAD.

This affect the behaviour of how threads are handled.

The tread-handling and interrupt-handling occurs in the driver itself.

An interrupt is handled immediately, the processing is offloaded to the threading.

## Example

> 
> * You touch the touchscreen


> * the touchscreen generates an interrupt


> * the driver handles the interrupt


> * a thread is created by the interrupt


> * the threadhandling read the I2C-bus

## Requirements

In order to create a working driver, I took it apart :

(split a complex problem into simple problems)

### a sample to detect interrupt

samples/basic/testirq

Each time the touchscreen gets touched, it increases a counter.

### a sample to scan the I2C-BUS

> (scanning the I2C_1 port),

### a sample to read the I2C-BUS

samples/basic/touched
It is based on the Hynitron touchscreen code.
Mass reading 63 bytes was not possible.

I did add a write of 1 to register 0x00.

### a samples to handle semaphores

samples/basic/testsemaphore
