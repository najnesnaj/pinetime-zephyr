.. _signing:

Signing an application
######################


.. code-block:: console


            imgtool.py sign --key ../../root-rsa-2048.pem \
                --header-size 0x200 \
                --align 8 \
                --version 1.2 \
                --slot-size 0x60000 \
                ../mcuboot/samples/zephyr/build/ds_d6/hello1/zephyr/zephyr.bin \
                signed-hello1.bin


