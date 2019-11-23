========================
Install zephyr 
========================

https://docs.zephyrproject.org/latest/getting_started/index.html

the documentation describes an installation process under Ubuntu/macOS/Windows


I picked Debian (which is not listed)
.... and soon afterwards ran into trouble


`this behaviour is known as : stuborn or stupid, but I remain convinced it could work`


But even after following the rules, I got a problem with the ``dtc (device tree compiler)``

  - I solved this by creating a link from the development-tools to /usr/bin/dtc (here you need to make sure you got a very recent one)

.. code-block:: console 

             cd  /root/zephyr-sdk-0.10.3/sysroots/x86_64-pokysdk-linux/usr/bin/
             mv dtc dtc-orig
             ln -s /usr/bin/dtc dtc





