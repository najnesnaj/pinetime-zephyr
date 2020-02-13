.. _infrastructure:

howto configure gateway 
=======================


Once you completed your ``west build`` , your image is located under the build directory


.. code-block:: console

    $ cd ~/work/pinetime/zephyr/build/zephyr
    here you can find zephyr.bin which you can flash 
    

::

      I use an orange pi single board computer.
      The pinetime watch is attached to this.
      My development is done on a laptop.


::

      How can you copy from one environment (laptop) to another (SBC) without typing password?

On the laptop :

.. code-block:: console

    ssh-keygen -b 8092 -t rsa -C "fota gw access key" -f ~/.ssh/orange
    Generating public/private rsa key pair.
    Enter passphrase (empty for no passphrase):          (LEAVE EMPTY!)
    Enter same passphrase again:
    Your identification has been saved in /root/.ssh/orange.
    Your public key has been saved in /root/.ssh/orange.pub.
    The key fingerprint is:
    SHA256:xCM5Fk1LAVjEWqrM6LKM8Y6+Y12ONt6eV8vDa/KdRUM fota gw access key
    The key's randomart image is:
    +---[RSA 8092]----+
    |     ==++.       |
    |B*B.o+. +ooo     |
    +----[SHA256]-----+

    (the standard port is 22 and not 9988 which is my custom port)    

    copy the certificate to the SBC (which name is orange in my case): 
    ssh-copy-id -p 9988 -i ~/.ssh/orange.pub root@orange


    create config file :  ~/.ssh/config
          Host orange
          HostName orange
          User root
          Port 9988
          IdentityFile ~/.ssh/orange




::

      Now you can copy without a password :
      scp build/zephyr/zephyr.bin orange:/usr/src 
