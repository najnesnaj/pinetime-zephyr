.. _mcuboot:



Wireless Device Firmware Upgrade
################################

Overview
********
In order to perform a FOTA (firmware over the air) update on zephyr you need 2 basic components:

        * MCUboot   (a bootloader)
        * SMP Server (a bluetooth service)






.. _mcuboot:



MCUboot with zephyr
###################




Installing Requirements and Dependencies
----------------------------------------

Clone MCUBOOT for zephyr from github.
Install additional packages required for development with mcuboot:

::

  cd ~/mcuboot  # or to your directory where mcuboot is cloned
  pip3 install --user -r scripts/requirements.txt


Building the bootloader itself
------------------------------


To build MCUboot, create a build directory in boot/zephyr, and build
it as follows:

::

  cd boot/zephyr
  mkdir build && cd build
  cmake -GNinja -DBOARD=pinetime ..
  ninja


After building the bootloader, the binaries should reside in
`build/zephyr/zephyr.{bin,hex,elf}`.

This image can be flashed as a normal application.


Building Applications for the bootloader
----------------------------------------


Some additional configuration is required to build applications for MCUboot.

This is handled internally by the Zephyr configuration system and is wrapped
in the `CONFIG_BOOTLOADER_MCUBOOT` Kconfig variable, which must be enabled in
the application's `prj.conf` file.


The Zephyr `CONFIG_BOOTLOADER_MCUBOOT` configuration option
[documentation](http://docs.zephyrproject.org/reference/kconfig/CONFIG_BOOTLOADER_MCUBOOT.html)
provides additional details regarding the changes it makes to the image
placement and generation in order for an application to be bootable by
MCUboot.


Signing the application
-----------------------

In order to upgrade to an image (or even boot it, if
`MCUBOOT_VALIDATE_PRIMARY_SLOT` is enabled), the images must be signed.

To make development easier, MCUboot is distributed with some example
keys.  It is important to stress that these should never be used for
production, since the private key is publicly available in this
repository.  See below on how to make your own signatures.

Images can be signed with the `scripts/imgtool.py` script.  It is best
to look at `samples/zephyr/Makefile` for examples on how to use this.

Flashing the application
------------------------

Since the bootloader is already in place, you cannot flash your application.bin to 0x00000.

Eg. in openocd : program application.bin 0x0c000. (which corresponds to the flash layout of slot 0)

These images can also be marked for upgrade, and loaded into the secondary slot,
at which point the bootloader should perform an upgrade.  

