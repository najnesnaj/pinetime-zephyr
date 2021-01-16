![image](./zephyr_logo.png)

# INDEX


* Copyright


    * author:


    * LICENSE:


* Zephyr for the pinetime smartwatch


* Install zephyr


    * update on 31-12-2020


    * In case you already have zephyr installed:


    * In case you start from scratch :


* Starting with some basic applications


    * Blinky    example


    * Reading out the button on the watch


        * Building and Running


* bluetooth (BLE) example


    * Using a standard zephyr application under pinetime:


    * Eddy Stone


    * Using the created bluetooth sample:


    * Ble Peripheral


    * using Python to read out bluetoothservices


* display (st7789)


    * Display    example


* GFX Library Sample


    * Overview


    * Usage


* LittlevGL Basic Sample


    * Overview


    * Simulation


    * Requirements


    * Building and Running


        * modifying the font size :


        * apply changes of the changed config:


    * Todo


    * References


* LittlevGL Clock Sample


    * Overview


    * Requirements


    * Building and Running


    * Todo


    * References


* Real Time Clock


    * Overview


    * Requirements


    * Building and Running


    * Todo


    * References


* Current Time Service


    * Requirements:


    * BLE Peripheral CTS sample for zephyr


    * Using bluez on linux to connect


    * Howto use Bluez on linux to set up a time service


    * Howto use Android to set up a time service


* Drivers


    * configuring I2C


        * board level definitions


        * definition on project level


    * sensors on the I2C bus


    * Bosch BMA421


        * Overview


        * Requirements


            * adapt CMakeLists.txt


            * adapt Kconfig


            * add yaml file


            * edit KConfig


            * create driver


        * Building and Running


        * Todo


        * References


    * HYNITRON CST816S


        * Overview


        * Requirements


            * create driver


        * Building and Running


        * Todo


        * References


    * HX HRS3300


        * Overview


        * Requirements


            * adapt CMakeLists.txt


            * adapt Kconfig


            * add yaml file


            * edit KConfig


            * create driver


        * Building and Running


        * Todo


        * References


    * Serial Nor Flash


        * Overview


            * consulting the generated board definition file


        * Requirements


        * Building and Running


        * Todo


        * References


    * Battery


        * Overview


        * Todo


        * References


    * Watchdog


        * Overview


        * Todo


        * References


* Firmware Over The Air (FOTA)


    * Wireless Device Firmware Upgrade


        * Overview


    * MCUboot with zephyr


    * Partitions


        * Defining partitions for MCUboot


        * Using NOR flash in partitions


    * Signing an application


        * Generating a new keypair


        * Extracting the public key


        * Example


    * SMP Server Sample


        * Overview


        * Requirements


        * Building and Running


            * Step 1: Build smp_svr


            * Step 2: Sign the image


            * Step 3: Flash the smp_svr image


            * Step 4: Run it!


            * Step 5: Device Firmware Upgrade


                * List the images


                * Test the image


                * Reset remotely


* Samples and Demos


    * Basic Samples


        * Blinky Application


            * Overview


            * Requirements


            * Building and Running


        * Button demo


            * Overview


            * Requirements


            * Building and Running


        * I2C Scanner sample


            * Overview


            * Building and Running


        * Touchscreen IRQ


            * Overview


            * Requirements


            * Building and Running


        * Touchpoints


            * Overview


            * Requirements


            * Building and Running


    * Sensor Samples


        * BMA280: Three Axis High-g I2C/SPI Accelerometer


            * Description


            * References


            * Wiring


                * I2C mode


                * SPI mode


            * Building and Running


                * Sample Output: Max Peak Detect Mode


                * Sample Output: Measurement Mode


        * CST816S HYNITRON TOUCHSCREEN


            * Description


            * References


            * Wiring


                * I2C mode


            * Building and Running


                * Sample Output: X & Y coordinates


                * Sample Output: Measurement Mode


        * HRS3300 Heart Rate Sensor


            * Overview


            * Building and Running


                * Sample Output


        * HRS3300 Heart Rate Sensor


            * Overview


            * Building and Running


                * Sample Output


    * Driver Samples


        * I2C Scanner sample


            * Overview


            * Building and Running


        * I2C Scanner sample


            * Overview


            * Building and Running


    * Display Samples


        * LittlevGL Basic Sample


            * Overview


            * Requirements


            * Building and Running


            * References


        * LittlevGL Basic Sample


            * Overview


            * Requirements


            * Building and Running


            * References


        * ST7789V Display driver


            * Overview


            * Building and Running


            * References


    * GUI Samples


        * Clock Sample Current Time Service


            * Overview


            * Requirements


            * Building and Running


            * References


        * Clock Sample Current Time Service


            * Overview


            * Requirements


            * Building and Running


            * References


        * LittlevGL Clock Sample


            * Overview


            * Requirements


            * Building and Running


            * References


        * Adafruit GFX Library on ST7789V Display


            * Overview


        * Display accel values


            * Overview


            * Requirements


            * Building and Running


            * References


        * LittlevGL Basic Sample


            * Overview


            * Requirements


            * Building and Running


            * References


        * Touchscreen Basic Sample


            * Overview


            * Requirements


            * Building and Running


            * References


    * Bluetooth Samples


        * Bluetooth: Central / Heart-rate Monitor


            * Overview


            * Requirements


            * Building and Running


        * Bluetooth: Eddystone


            * Overview


            * Requirements


            * Building and Running


        * Bluetooth: Peripheral_cts


            * Overview


            * Requirements


            * Building and Running


        * Bluetooth: Peripheral


            * Overview


            * Requirements


            * Building and Running


* Menuconfig


    * Zephyr is like linux


* Hacking stuff


    * hacking   the pinetime smartwatch


    * debugging   the pinetime smartwatch


    * scanning the I2C_1 port


        * Building and Running


    * howto flash your zephyr image


    * howto remove the write protection


    * howto configure gateway


    * howto use 2 openocd sessions


        * Suppose you have 2 microcontrollers


        * Howto setup a second openocd session on a different port?


        * Howto use the GPIO header of a Single Board computer


    * howto generate pdf documents


* Behind the scene


    * Behind the scene


        * Overview


    * development trajectory


    * Bosch BMA280


        * Overview


        * Requirements


        * Building and Running


        * Todo


        * References


    * Touchscreen Hynitron


        * Overview


        * Requirements


        * Building and Running


        * Todo


        * References


    * Troubleshooting drivers


        * Overview


        * Example


        * Requirements


            * a sample to detect interrupt


            * a sample to scan the I2C-BUS


            * a sample to read the I2C-BUS


            * a samples to handle semaphores


    * placing a button on the screen


        * Building and Running


* About


    * Todo
