# configuring I2C

## board level definitions

```
under boards/arm/pinetime are the board definitions
- pinetime.dts
- pinetime_defconfig


The sensors in the pinetime use the I2C bus.

&i2c1 {
        compatible = "nordic,nrf-twi";
        status = "okay";
        sda-pin = <6>;
        scl-pin = <7>;

      };
```

## definition on project level

In the directory of a sample, you will find a prj.conf file.
Here you can set values specific for you project/sample.

```
In the "prj.conf" file we define the sensor (eg adxl372)

CONFIG_STDOUT_CONSOLE=y
CONFIG_LOG=y
CONFIG_I2C=y
CONFIG_SENSOR=y
CONFIG_ADXL372=y
CONFIG_ADXL372_I2C=y
CONFIG_SENSOR_LOG_LEVEL_WRN=y
```

**note: this gets somehow merged (overlayed) with the board definition pinetime_defconfig**
