#!/usr/bin/env python3

# Python application to add a Bluetooth Current Time Service to a Linux Bluez
# server. Connection to Bluez is using DBus. Adapted from the HRS and Battery
# GATT server example.


import dbus
import dbus.exceptions
import dbus.mainloop.glib
import dbus.service
import logging

try:
    from gi.repository import GObject
except ImportError:
    import gobject as GObject

# TODO: remove
# import sys

import time

BLUEZ_SERVICE_NAME = 'org.bluez'
GATT_MANAGER_IFACE = 'org.bluez.GattManager1'
DBUS_OM_IFACE = 'org.freedesktop.DBus.ObjectManager'
DBUS_PROP_IFACE = 'org.freedesktop.DBus.Properties'

GATT_SERVICE_IFACE = 'org.bluez.GattService1'
GATT_CHRC_IFACE = 'org.bluez.GattCharacteristic1'
GATT_DESC_IFACE = 'org.bluez.GattDescriptor1'


class InvalidArgsException(dbus.exceptions.DBusException):
    _dbus_error_name = 'org.freedesktop.DBus.Error.InvalidArgs'


class NotSupportedException(dbus.exceptions.DBusException):
    _dbus_error_name = 'org.bluez.Error.NotSupported'


class NotPermittedException(dbus.exceptions.DBusException):
    _dbus_error_name = 'org.bluez.Error.NotPermitted'


class InvalidValueLengthException(dbus.exceptions.DBusException):
    _dbus_error_name = 'org.bluez.Error.InvalidValueLength'


class FailedException(dbus.exceptions.DBusException):
    _dbus_error_name = 'org.bluez.Error.Failed'


class Application(dbus.service.Object):
    """
    org.bluez.GattApplication1 interface implementation
    """
    def __init__(self, bus):
        self.path = '/'
        self.services = []
        dbus.service.Object.__init__(self, bus, self.path)
        self.add_service(CurrentTimeService(bus, 0))

    def get_path(self):
        return dbus.ObjectPath(self.path)

    def add_service(self, service):
        self.services.append(service)

    @dbus.service.method(DBUS_OM_IFACE, out_signature='a{oa{sa{sv}}}')
    def GetManagedObjects(self):
        response = {}
        for service in self.services:
            response[service.get_path()] = service.get_properties()
            chrcs = service.get_characteristics()
            for chrc in chrcs:
                response[chrc.get_path()] = chrc.get_properties()
                descs = chrc.get_descriptors()
                for desc in descs:
                    response[desc.get_path()] = desc.get_properties()

        return response


class Service(dbus.service.Object):
    """
    org.bluez.GattService1 interface implementation
    """
    PATH_BASE = '/org/bluez/example/service'

    def __init__(self, bus, index, uuid, primary):
        self.path = self.PATH_BASE + str(index)
        self.bus = bus
        self.uuid = uuid
        self.primary = primary
        self.characteristics = []
        dbus.service.Object.__init__(self, bus, self.path)

    def get_properties(self):
        return {
                GATT_SERVICE_IFACE: {
                        'UUID': self.uuid,
                        'Primary': self.primary,
                        'Characteristics': dbus.Array(
                                self.get_characteristic_paths(),
                                signature='o')
                }
        }

    def get_path(self):
        return dbus.ObjectPath(self.path)

    def add_characteristic(self, characteristic):
        self.characteristics.append(characteristic)

    def get_characteristic_paths(self):
        result = []
        for chrc in self.characteristics:
            result.append(chrc.get_path())
        return result

    def get_characteristics(self):
        return self.characteristics

    @dbus.service.method(DBUS_PROP_IFACE,
                         in_signature='s',
                         out_signature='a{sv}')
    def GetAll(self, interface):
        if interface != GATT_SERVICE_IFACE:
            raise InvalidArgsException()

        return self.get_properties()[GATT_SERVICE_IFACE]


class Characteristic(dbus.service.Object):
    """
    org.bluez.GattCharacteristic1 interface implementation
    """
    def __init__(self, bus, index, uuid, flags, service):
        self.path = service.path + '/char' + str(index)
        self.bus = bus
        self.uuid = uuid
        self.service = service
        self.flags = flags
        self.descriptors = []
        dbus.service.Object.__init__(self, bus, self.path)

    def get_properties(self):
        return {
                GATT_CHRC_IFACE: {
                        'Service': self.service.get_path(),
                        'UUID': self.uuid,
                        'Flags': self.flags,
                        'Descriptors': dbus.Array(
                                self.get_descriptor_paths(),
                                signature='o')
                }
        }

    def get_path(self):
        return dbus.ObjectPath(self.path)

    def add_descriptor(self, descriptor):
        self.descriptors.append(descriptor)

    def get_descriptor_paths(self):
        result = []
        for desc in self.descriptors:
            result.append(desc.get_path())
        return result

    def get_descriptors(self):
        return self.descriptors

    @dbus.service.method(DBUS_PROP_IFACE,
                         in_signature='s',
                         out_signature='a{sv}')
    def GetAll(self, interface):
        if interface != GATT_CHRC_IFACE:
            raise InvalidArgsException()

        return self.get_properties()[GATT_CHRC_IFACE]

    @dbus.service.method(GATT_CHRC_IFACE,
                         in_signature='a{sv}',
                         out_signature='ay')
    def ReadValue(self, options):
        logging.error('Default ReadValue called, returning error')
        raise NotSupportedException()

    @dbus.service.method(GATT_CHRC_IFACE, in_signature='aya{sv}')
    def WriteValue(self, value, options):
        logging.error('Default WriteValue called, returning error')
        raise NotSupportedException()

    @dbus.service.method(GATT_CHRC_IFACE)
    def StartNotify(self):
        logging.error('Default StartNotify called, returning error')
        raise NotSupportedException()

    @dbus.service.method(GATT_CHRC_IFACE)
    def StopNotify(self):
        logging.error('Default StopNotify called, returning error')
        raise NotSupportedException()

    @dbus.service.signal(DBUS_PROP_IFACE,
                         signature='sa{sv}as')
    def PropertiesChanged(self, interface, changed, invalidated):
        pass


class Descriptor(dbus.service.Object):
    """
    org.bluez.GattDescriptor1 interface implementation
    """
    def __init__(self, bus, index, uuid, flags, characteristic):
        self.path = characteristic.path + '/desc' + str(index)
        self.bus = bus
        self.uuid = uuid
        self.flags = flags
        self.chrc = characteristic
        dbus.service.Object.__init__(self, bus, self.path)

    def get_properties(self):
        return {
                GATT_DESC_IFACE: {
                        'Characteristic': self.chrc.get_path(),
                        'UUID': self.uuid,
                        'Flags': self.flags,
                }
        }

    def get_path(self):
        return dbus.ObjectPath(self.path)

    @dbus.service.method(DBUS_PROP_IFACE,
                         in_signature='s',
                         out_signature='a{sv}')
    def GetAll(self, interface):
        if interface != GATT_DESC_IFACE:
            raise InvalidArgsException()

        return self.get_properties()[GATT_DESC_IFACE]

    @dbus.service.method(GATT_DESC_IFACE,
                         in_signature='a{sv}',
                         out_signature='ay')
    def ReadValue(self, options):
        logging.error('Default ReadValue called, returning error')
        raise NotSupportedException()

    @dbus.service.method(GATT_DESC_IFACE, in_signature='aya{sv}')
    def WriteValue(self, value, options):
        logging.error('Default WriteValue called, returning error')
        raise NotSupportedException()


class CurrentTimeService(Service):
    """
    Fake Battery service that emulates a draining battery.

    """
    CURRENT_TIME_UUID = '1805'

    def __init__(self, bus, index):
        Service.__init__(self, bus, index, self.CURRENT_TIME_UUID, True)
        self.add_characteristic(CurrentTimeCharacteristic(bus, 0, self))


class CurrentTimeCharacteristic(Characteristic):
    """
    Fake Battery Level characteristic. The battery level is drained by 2 points
    every 5 seconds.

    """
    CURRENT_TIME_UUID = '2a2B'

    def __init__(self, bus, index, service):
        Characteristic.__init__(
                self, bus, index,
                self.CURRENT_TIME_UUID,
                ['read', 'notify'],
                service)
        self.notifying = False
        GObject.timeout_add(5000, self.notify_time)

    def current_time_bytes(self):
        dt = time.localtime()
        year = dt.tm_year.to_bytes(2, 'little')
        value = list([dbus.Byte(b) for b in year])
        value.append(dbus.Byte(dt.tm_mon))
        value.append(dbus.Byte(dt.tm_mday))
        value.append(dbus.Byte(dt.tm_hour))
        value.append(dbus.Byte(dt.tm_min))
        value.append(dbus.Byte(dt.tm_sec))
        value.append(dbus.Byte(dt.tm_wday))
        value.append(dbus.Byte(0))
        value.append(dbus.Byte(1))
        return value

    def notify_current_time(self):
        if not self.notifying:
            return
        self.PropertiesChanged(
                GATT_CHRC_IFACE,
                {'Value': self.current_time_bytes()}, [])

    def notify_time(self):
        if not self.notifying:
            return True
        logging.info('Notifying current local time')
        self.notify_current_time()
        return True

    def ReadValue(self, options):
        value = self.current_time_bytes()
        logging.info("Supplying time")
        return value

    def StartNotify(self):
        if self.notifying:
            logging.warning('Already notifying, nothing to do')
            return
        self.notifying = True
        self.notify_current_time()

    def StopNotify(self):
        if not self.notifying:
            logging.warning('Not notifying, nothing to do')
            return

        self.notifying = False


class server(object):

    def register_app_cb(self):
        logging.info('GATT application registered')

    def register_app_error_cb(self, error):
        logging.error('Failed to register application: ' + str(error))
        self.mainloop.quit()

    def find_adapter(self, bus):
        remote_om = dbus.Interface(bus.get_object(BLUEZ_SERVICE_NAME, '/'),
                                   DBUS_OM_IFACE)
        objects = remote_om.GetManagedObjects()

        for o, props in objects.items():
            if GATT_MANAGER_IFACE in props.keys():
                return o

        return None

    def __init__(self):
        logger = logging.getLogger('')
        logger.setLevel(logging.INFO)

        dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

        bus = dbus.SystemBus()

        adapter = self.find_adapter(bus)
        if not adapter:
            logging.error('GattManager1 interface not found')
            return

        service_manager = dbus.Interface(
                bus.get_object(BLUEZ_SERVICE_NAME, adapter),
                GATT_MANAGER_IFACE)

        app = Application(bus)

        self.mainloop = GObject.MainLoop()

        logging.info('Registering GATT application...')

        service_manager.RegisterApplication(
                app.get_path(), {},
                reply_handler=self.register_app_cb,
                error_handler=self.register_app_error_cb)

    def run(self):
        self.mainloop.run()


if __name__ == '__main__':
    server().run()
