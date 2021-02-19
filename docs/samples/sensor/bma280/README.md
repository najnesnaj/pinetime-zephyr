# BMA280: Three Axis High-g I2C/SPI Accelerometer

## Description

This sample application produces slightly different outputs based on the chosen
driver configuration mode:


* In **Measuring Mode with trigger support**,
the acceleration on all three axis is printed in m/s^2 at the sampling rate (ODR).


* In **Polled Measuring Mode**, the instantaneous acceleration is polled every 2 seconds.


* In **Max Peak Detect Mode**, the device returns only the over-threshold
peak acceleration between two consecutive sample fetches or trigger events.
(In most high-g applications, a single 3-axis acceleration sample at the peak
of an impact event contains sufficient information about the event, and the
full acceleration history is not required.) Instead of printing the acceleration
on all three axis, the sample application calculates the vector magnitude
(root sum squared) and displays the result in g’s rather than in m/s^2,
together with an bar graph.

## References


* BMA280: [http://www.analog.com/bma280](http://www.analog.com/bma280)

## Wiring

This sample uses the BMA280 sensor controlled either using the I2C or SPI interface.
Connect supply **VDD**, **VS** and **GND**. The supply voltage can be in
the 1.6V to 3.5V range.

### I2C mode

Connect Interface: **SDA**, **SCL** and optionally connect the **INT1** to a
interrupt capable GPIO. It is a requirement that **SCLK** must be connected to
**GND** in I2C mode. Depending on the baseboard used, the **SDA** and **SCL**
lines require Pull-Up resistors. With the **MISO** pin low, the I2C address for
the device is 0x1D, and an alternate I2C address of 0x53 can be chosen by
pulling the **MISO** pin high.

I2C Address:


* **0x1D**: if MISO is pulled low


* **0x53**: if MISO is pulled high

**NOTE**: When sharing an SDA bus, the BMA280 Silicon Revision < 3  may prevent
communication with other devices on that bus.

### SPI mode

Connect Interface: **SCLK**, **MISO**, **MOSI** and **/CS** and optionally
connect the **INT1** to a interrupt capable GPIO.

## Building and Running

This project outputs sensor data to the console. It requires an BMA280
sensor. It should work with any platform featuring a I2C/SPI peripheral interface.
It does not work on QEMU.

### Sample Output: Max Peak Detect Mode

### Sample Output: Measurement Mode
