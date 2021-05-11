[NEW] Characteristic

    /org/bluez/hci0/dev_F6_2C_86_BD_4A_05/service0014/char0015
    12345678-1234-5678-1234-56789abcdef1
    Vendor specific

[NEW] Characteristic

    /org/bluez/hci0/dev_F6_2C_86_BD_4A_05/service0014/char0018
    12345678-1234-5678-1234-56789abcdef2
    Vendor specific

[dsd6]# info
Device F6:2C:86:BD:4A:05 (random)

> Name: dsd6
> Alias: dsd6
> Appearance: 0x0341
> Paired: no
> Trusted: no
> Blocked: no
> Connected: yes
> LegacyPairing: no
> UUID: Generic Access Profile    (00001800-0000-1000-8000-00805f9b34fb)
> UUID: Generic Attribute Profile (00001801-0000-1000-8000-00805f9b34fb)
> UUID: Battery Service           (0000180f-0000-1000-8000-00805f9b34fb)
> UUID: Vendor specific           (12345678-1234-5678-1234-56789abcdef0)

[dsd6]# menu gatt

[dsd6]# attribute-info 12345678-1234-5678-1234-56789abcdef2
Characteristic - Vendor specific

> UUID: 12345678-1234-5678-1234-56789abcdef2
> Service: /org/bluez/hci0/dev_F6_2C_86_BD_4A_05/service0014
> Flags: read
> Flags: write

[dsd6]# attribute-info 12345678-1234-5678-1234-56789abcdef1
Characteristic - Vendor specific

> UUID: 12345678-1234-5678-1234-56789abcdef1
> Service: /org/bluez/hci0/dev_F6_2C_86_BD_4A_05/service0014
> Notifying: no
> Flags: notify
