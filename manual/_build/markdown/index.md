![image](./zephyr_logo.png)

# INDEX


* Copyright


    * author:


    * LICENSE:


* Zephyr  smartwatch framework


* The idea behind the framework


    * Building blocks


    * Screen


    * Touchscreen


    * Heart rate sensor


    * Bluetooth


    * Power saving


    * Updating over the air


    * Motion sensor


    * Drivers


* Install zephyr


    * update on 31-12-2020


    * How to install zephyr


    * How to install the open source watch frame kit


    * Linux rules


* Out of tree


    * Top Tip:


* display


    * Display   Types


        * Several methods of using the display


        * The human eye


* Starting with some basic applications


    * Push the button


    * posix


        * Building and Running


    * pinetime


        * Building and Running


            * Reading out the button on the watch


* LittlevGL Basic Sample


    * Overview


    * Simulation


    * Pinetime


    * Building and Running


        * modifying the font size :


        * apply changes of the changed config:


    * References


* Real Time Clock


    * Overview


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


    * SSD1306 modification


        * board level definitions


        * definition config


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


* bluetooth (BLE)


    * A word on bluetooth-serial communication


    * Eddy Stone


    * Using the created bluetooth sample:


        * the no-bluetooth, no-watch approach : nrf52_bsim


        * the no-watch approach : simulation on a laptop


    * Bluez


        * using bluez to write something to the device


    * using Python to read out bluetoothservices


* Bluetooth Notification


    * What?


    * How?


    * Bluez


    * A word on attributes


    * Attribute Handle


    * Python


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


* Samples


    * Battery OSWatch Framework


        * Todo


        * Overview


        * Requirements


        * Building and Running


        * References


    * OSWatch bluetooth setting parameters


        * Overview


        * Bluetooth


        * Requirements


        * Building and Running


        * References


    * Setting up an alarm/calendar event


        * Overview


        * Requirements


        * Building and Running


        * References


    * Current Time Setting  OSWatch Framework


        * Overview


        * Requirements


        * Building and Running


        * References


    * FOTA OSWatch Framework


        * Todo


        * Overview


        * Requirements


        * Building and Running


        * References


    * Basic OSWatch Framework


        * Overview


        * Remark


        * Requirements


        * Building and Running


        * References


    * HRS3300 Heart Rate Sensor


        * Overview


        * Building and Running


            * Sample Output


    * Bluetooth: Central / Heart-rate Monitor


        * Overview


        * Requirements


        * Building and Running


    * Bluetooth: transferring data to the watch


        * Overview


        * Requirements


        * Building and Running


    * Bluetooth: getting data from the watch


        * Overview


        * Requirements


        * Building and Running


    * Bluetooth: transferring data to the watch


        * Overview


        * Requirements


        * Building and Running


    * Pinetime  Button  Sample


        * Overview


        * Requirements


        * Building and Running


        * References


    * SDL Button Timer  Sample


        * Overview


        * Requirements


        * Building and Running


        * References


    * LittlevGL SDL Button  Sample


        * Overview


        * Requirements


        * Building and Running


        * References


    * Character frame buffer


        * Overview


        * Building and Running


        * POSIX


        * Pinetime


    * Character Framebuffer Shell Module Sample


        * Overview


        * Building and Running


            * Shell Module Command Help


    * LittlevGL Basic Sample


        * Overview


        * Requirements


        * Building and Running


        * References


    * Lightsensor


    * Testing the timer refresh


        * Overview


        * Requirements


        * Building and Running


        * References


* Menuconfig


    * Zephyr is like linux


* Debugging


    * debugging


        * Segger JLink


        * Black Magic


        * STM32 - Raspberry - OpenOCD


    * debugging Posix


    * The black magic probe


        * probes in zephyr


        * howto setup a blackmagicprobe


    * pseudo


        * simulation on NATIVE_POSIX_64


    * Bsim


        * debugging on nrf52_bsim


    * Segger RTT (Real Time Transfer)


    * Serial data without a serial port


* Hacking stuff


    * hacking   the pinetime smartwatch


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


    * The Movie


        * editing :


        * script :


        * Camera :


        * Voice over :


        * Music by Beethoven:


* Behind the scene


    * Touchscreen


        * Overview


        * Requirements


        * Building and Running


        * Todo


        * References


    * placing a button on the screen


        * Building and Running


* About


* Author
