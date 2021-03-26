Serial Nor Flash
################


.. code-block:: console

      west build -p -b pinetime samples/drivers/spi_flash -DCONF=prj.conf 






Overview
********

This sample application should unlock the serial nor flash memory. 
This can be very useful to store e.g. background for the watch.

compilation problematic ....

/root/zephyrproject/zephyr/samples/drivers/spi_flash/src/main.c:17:22: error: 'DT_INST_0_JEDEC_SPI_NOR_LABEL' undeclared (first use in this function); did you mean 'DT_INST_0_NORDIC_NRF_RTC_LABEL'?


Turns out this is some problem with the board definition file.

I found it to be very useful to consult the generated dts file.
Here you can check if everything is present.

Guess the dts-file has to be well intended.(structured)


**TIP: consult the generated dts board file **


consulting the generated board definition file
----------------------------------------------


.. code-block:: console

     vi /root/zephyrproject/zephyr/build/zephyr/include/generated/generated_dts_board.conf




Requirements
************

complement the pinetime.dts file with the following (under spi)
#define JEDEC_ID_MACRONIX_MX25L64      0xC22017

.. code-block:: console





      &spi0 {
        compatible = "nordic,nrf-spi"; 
	status = "okay";
        sck-pin = <2>;
        mosi-pin = <3>;
        miso-pin = <4>;
	cs-gpios = <&gpio0 27 0>,<&gpio0 5 0>;
	st7789v@0 {
		compatible = "sitronix,st7789v";
		label = "DISPLAY";
		spi-max-frequency = <8000000>;
		reg = <0>;
		cmd-data-gpios = <&gpio0 18 0>;
		reset-gpios = <&gpio0 26 0>;
		width = <240>;
		height = <240>;
		x-offset = <0>;
		y-offset = <0>;
                vcom = <0x19>;
		gctrl = <0x35>;
		vrhs = <0x12>;
		vdvs = <0x20>;
		mdac = <0x00>;
		gamma = <0x01>;
		colmod = <0x05>;
		lcm = <0x2c>;
		porch-param = [0c 0c 00 33 33];
		cmd2en-param = [5a 69 02 01];
		pwctrl1-param = [a4 a1];
                pvgam-param = [D0 04 0D 11 13 2B 3F 54 4C 18 0D 0B 1F 23];
		nvgam-param = [D0 04 0C 11 13 2C 3F 44 51 2F 1F 1F 20 23];
		ram-param = [00 F0];
		rgb-param = [CD 08 14];

        };

        mx25r64: mx25r6435f@1 {
		compatible = "jedec,spi-nor";
		reg = <1>;
		spi-max-frequency = <1000000>;
		label = "MX25R64";
		jedec-id = [0b 40 16];
		size = <67108864>;
		has-be32k;
	};



Building and Running
********************


.. code-block:: console

             west build -p -b pinetime samples/drivers/spi_flash

Todo
****

    - detect ID memory  : it is not the macronix one as suggestion on the pinetime website

    I found the following : jedec-id = [0b 40 16]; (OK: can execute sample program)

    - create working board definition (OK: see above) 

References
**********

http://files.pine64.org/doc/datasheet/pinetime/MX25L6433F,%203V,%2064Mb,%20v1.6.pdf

