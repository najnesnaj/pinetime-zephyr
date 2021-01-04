.. _cts:

Current Time Service
####################

Overview
********

The bluetooth peripheral sample has a cts server in place.
By installing this sample on a bluetoothboard, one can simulate the CTS.

Another option is to use a smartphone or computer to connect and bond to your Pinetime. 
As soon as a device is bonded, Pinetime will look for a CTS server (Current Time Service) on the connected device.

Here is how to do it with an Android smartphone running NRFConnect:
Build and program the firmware on the Pinetime
Install NRFConnect (https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop)
Start NRFConnect and create a CTS server : 
Tap the hamburger button on the top left and select "Configure GATT server"
Tap "Add service" on the bottom
Select server configuration "Current Time Service" and tap OK
Go back to the main screen and scan for BLE devices. A device called "PineTime" should appear
Tap the button "Connect" next to the PineTime device. It should connect to the PineTime and switch to a new tab.
On this tab, on the top right, there is a 3 dots button. Tap on it and select Bond. The bonding process begins, and if it is sucessful, the PineTime should update its time and display it on the screen.





Requirements
************




Building and Running
********************



.. code-block:: console

       west build -p -b pinetime samples/bluetooth/peripheral-cts


Todo
****

    - make it work 


References
**********

