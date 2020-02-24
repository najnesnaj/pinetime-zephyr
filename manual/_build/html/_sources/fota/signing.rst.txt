.. _signing:

Signing an application
######################



In order to improve the security, only signed images can be uploaded.

There is a public and private key.
The Bootloader is compiled with the public key.
Each time you want to upload firmware, you have to sign it with a private key.


**NOTE: it is important to keep the private key hidden**

Generating a new keypair
------------------------
Generating a keypair with imgtool is a matter of running the keygen
subcommand:

.. code-block:: console


    $ ./scripts/imgtool.py keygen -k mykey.pem -t rsa-2048



Extracting the public key
-------------------------

The generated keypair above contains both the public and the private
key.  It is necessary to extract the public key and insert it into the
bootloader.  

.. code-block:: console

    $ ./scripts/imgtool.py getpub -k mykey.pem

This will output the public key as a C array that can be dropped
directly into the `keys.c` file.


Example
-------

sign the compiled zephyr.bin firmware with the root-rsa-2048.pem, private key:


.. code-block:: console


            imgtool.py sign --key ../../root-rsa-2048.pem \
                --header-size 0x200 \
                --align 8 \
                --version 1.2 \
                --slot-size 0x60000 \
                ../mcuboot/samples/zephyr/build/ds_d6/hello1/zephyr/zephyr.bin \
                signed-hello1.bin


