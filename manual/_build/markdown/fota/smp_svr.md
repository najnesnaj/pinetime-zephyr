# SMP Server Sample

## Overview

This sample application implements a Simple Management Protocol (SMP) server.
SMP is a basic transfer encoding for use with the MCUmgr management protocol.

This sample application supports the following mcumgr transports by default:

> 
> * Shell


> * Bluetooth

## Requirements

In order to communicate with the smp server sample installed on your pinetime, you need mcumgr.

Here is a procedure to install mcumgr on a raspberry pi  (or similar)

It is written in the go-language. You need to adapt the path :   PATH=$PATH:/root/go/bin.

## Building and Running

The sample will let you manage the pinetime over bluetooth. (via SMP protocol)

There are slot0 and slot1 which can both contain firmware.

Suppose you switch from slot0 to slot1, you still want to be able to communicate.

So both slots need smp_svr software!

### Step 1: Build smp_svr

`smp_svr` can be built for the nRF52 as follows:

**NOTE: to perform a firmware update over the air, you have to build a second sample**

### Step 2: Sign the image

Using MCUboot's `imgtool.py` script, sign the `zephyr.(bin|hex)`
file you built in Step 3. In the below example, the MCUboot repo is located at
`~/src/mcuboot`.

```
~/src/mcuboot/scripts/imgtool.py sign \
     --key ~/src/mcuboot/root-rsa-2048.pem \
     --header-size 0x200 \
     --align 8 \
     --version 1.0 \
     --slot-size <image-slot-size> \
     <path-to-zephyr.(bin|hex)> signed.(bin|hex)
```

The above command creates an image file called `signed.(bin|hex)` in the
current directory.

### Step 3: Flash the smp_svr image

Upload the bin-file from Step 2 to image slot-0.
For the pinetime, slot-0 is located at address `0xc000`.

```
in openocd : program zephyr.bin 0xc000
```

### Step 4: Run it!

**NOTE**: If you haven't installed `mcumgr` yet, then do so by following the
instructions in the mcumgr_cli section of the Management subsystem
documentation.

The `smp_svr` app is ready to run.  Just reset your board and test the app
with the `mcumgr` command-line tool's `echo` functionality, which will
send a string to the remote target device and have it echo it back:

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' echo hello
hello
```

### Step 5: Device Firmware Upgrade

Now that the SMP server is running on your pinetime, you are able to communicate
with it using mcumgr.

You might want to test "OTA DFU", or Over-The-Air Device Firmware Upgrade.

To do this, build a second sample (following the steps below) to verify
it is sent over the air and properly flashed into slot-1, and then
swapped into slot-0 by MCUboot.

```
* Build a second sample
* Sign the second sample
* Upload the image over BLE
```

Now we are ready to send or upload the image over BLE to the target remote
device.

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' image upload signed.bin
```

If all goes well the image will now be stored in slot-1, ready to be swapped
into slot-0 and executed.

**NOTE**: At the beginning of the upload process, the target might start erasing
the image slot, taking several dozen seconds for some targets.  This might
cause an NMP timeout in the management protocol tool. Use the
`-t <timeout-in-seconds` option to increase the response timeout for the
`mcumgr` command line tool if this occurs.

#### List the images

We can now obtain a list of images (slot-0 and slot-1) present in the remote
target device by issuing the following command:

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' image list
```

This should print the status and hash values of each of the images present.

#### Test the image

In order to instruct MCUboot to swap the images we need to test the image first,
making sure it boots:

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' image test <hash of slot-1 image>
```

Now MCUBoot will swap the image on the next reset.

#### Reset remotely

We can reset the device remotely to observe (use the console output) how
MCUboot swaps the images:

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' reset
```

Upon reset MCUboot will swap slot-0 and slot-1.

You can confirm the new image and make the swap permanent by using this command:

```
sudo mcumgr --conntype ble --connstring ctlr_name=hci0,peer_name='Zephyr' image confirm
```

**Note** that if you try to send the very same image that is already flashed in
slot-0 then the procedure will not complete successfully since the hash values
for both slots will be identical.
