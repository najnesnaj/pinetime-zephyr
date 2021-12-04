PID controller/timer for beer production 
-----------------------------------------

used PID from : https://github.com/pms67/PID 

and compiled it : sdcc -mstm8 -c  PID.c this does give you :  PID.rel


There are some limitations in SDCC, in which it cannot compile and link multiple files, so my workaround is to compile the pid-program once and link it from within the make file.

one vessel (bag brewing)
------------------------

I use a kettle of 10l and an electric cooking plate, which I drive with an SSR (solid state relay of 20A)

 

simply beer? 
--------------------------------

parameters are hardcoded for Belgian trappist style beer (wanted to keep setup as simple as possible)

                                read_display_temp(45); //pre heat temp
                                real_time.minute=45;
                                read_display_temp(62); //maisch temp1
                                real_time.minute=30;
                                read_display_temp(71); //maisch temp2
                                real_time.minute=15;
                                read_display_temp(78); //filter temp

start
-----
temp sensor on the bottom
fill kettle with water and barley and power the stm8
still need to stir (this is not cool, will have to come up with solution for this)

after some time the barley is converted into sugar! (sg = 1085)

==================================================

it uses cheap components and cheap development


a TM1637 4 segment LED display -- very cheap = 60 cent

stm8 board -- very cheap = 60 cent

It would like to thank tiger762 : https://github.com/tiger762/STM8S103
and rogerdahl : https://github.com/rogerdahl/stm32-tm1637  
which code is used.





As far as software packages, you'll need at the very least, the SDCC compiler and a way to upload the resulting IHX file to the device:

On my Orange Pi running Armbian:

apt-get install sdcc

(optional if you want serial comms back to the host) apt-get install minicom

git clone http://github.com/vdudouyt/stm8flash
cd stm8flash
make
make install

The hardware programmer is sold on Ebay for around $4 each. Look for "st-link v2". Note that a hardware programmer is required to program the stm8 family. There is not a serial uploader installed like the stm32 has.


I used serial port of Orange Pi for debugging : #minicom -b 115200 -D /dev/ttyS1 (pin 38 - 40 on the GPIO)

Optional but extremely useful:
Saleae Logic Analyzer (About $7 each) -- to see up to 8 channels of digital waveform. EXTREMELY useful for debugging I2C. Seriously...

