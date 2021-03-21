#!/usr/bin/env python
from ctypes import cdll, c_int, c_uint8
from time import sleep

_libwdactions = cdll.LoadLibrary("../pi/.libs/libwdactions.so")


class PiWatchDog:
    def __init__(self, watchdogAddress: int):
        super().__init__()
        self.watchdog = _libwdactions.createWatchdog(watchdogAddress)

    @classmethod
    def fanOnMessage(cls, id: int):
        return _libwdactions.fanOnMessage(c_uint8(id))

    @classmethod
    def fanOffMessage(cls, id: int):
        return _libwdactions.fanOffMessage(c_uint8(id))

    @classmethod
    def powerOnMessage(cls, id: int):
        return _libwdactions.powerOnMessage(c_uint8(id))

    @classmethod
    def powerOffMessage(cls, id: int):
        return _libwdactions.powerOffMessage(c_uint8(id))

    @classmethod
    def kickDogMessage(cls, id: int):
        return _libwdactions.kickDogMessage(c_uint8(id))

    def _sendMessage(self, message):
        return _libwdactions.sendMessage(self.watchdog, message)

    def fanOn(self, id: int):
        self._sendMessage(self.fanOnMessage(id))

    def fanOff(self, id: int):
        self._sendMessage(self.fanOffMessage(id))

    def powerOn(self, id: int):
        self._sendMessage(self.powerOnMessage(id))

    def powerOff(self, id: int):
        self._sendMessage(self.powerOffMessage(id))

    def kickDog(self, id: int):
        self.powerOn(id)
        # print(f'I do not know how to kick a dog yet')
        self._sendMessage(self.kickDogMessage(id))


if __name__ == "__main__":
    # execute only if run as a script
    print("hello")

    wdaddr = c_int(0x08)
    watchdog = PiWatchDog(wdaddr)

    watchdog.fanOn(0)

    sleep(5)

    watchdog.fanOff(0)