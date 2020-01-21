configuring I2C
+++++++++++++++

board level definitions
-----------------------


::



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





development trajectory
----------------------

        
The final goal is to use the accel-sensor in the watch (BMA423), which does not exist yet.
In order to minimize the effort:

        - we'll use something that looks like it (ADXL372), because there exists an example.
        - next we adapt it to use the existing BMA280 sensor (under drivers/sensor)
        - finally we create a driver for the BMA423, based upon the BMA280





defining an I2C sensor
----------------------


::

    under samples/sensor/axl372 we create : "pinetime.overlay"
    &i2c1 {
        status = "okay";
        clock-frequency = <I2C_BITRATE_STANDARD>;
        adxl372@18 {
                   compatible = "adi,adxl372";
                   reg = <0x18>;
                   label = "ADXL372";
                   int1-gpios = <&gpio0 8 0>;
                   };
        };

**note: this gets somehow merged with the board definition pinetime.dts**




:: 



       In the "prj.conf" file we define the sensor

       CONFIG_STDOUT_CONSOLE=y
       CONFIG_LOG=y
       CONFIG_I2C=y
       CONFIG_SENSOR=y
       CONFIG_ADXL372=y
       CONFIG_ADXL372_I2C=y
       CONFIG_SENSOR_LOG_LEVEL_WRN=y

**note: this gets somehow merged with the board definition pinetime_defconfig**


       
compiling the sample
--------------------

::

         west build -p -b pinetime samples/sensor/adxl372 -DCONF=prj.conf
