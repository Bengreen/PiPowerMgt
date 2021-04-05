#!/usr/bin/env python
from ctypes import cdll, c_int, c_uint8, c_uint16
from time import sleep

_libwdactions = cdll.LoadLibrary("../pi/.libs/libwdactions.so")


class PiWatchDog:
    def __init__(self, watchdogAddress: int):
        super().__init__()
        self.watchdog = _libwdactions.createWatchdog(watchdogAddress)

    def fanOn(self, id: int, wait: int = 0):
        return _libwdactions.fanOn(self.watchdog, id, wait)

    def fanOff(self, id: int, wait: int = 0):
        return _libwdactions.fanOff(self.watchdog, id, wait)

    def powerOn(self, id: int, wait: int = 0):
        return _libwdactions.powerOn(self.watchdog, id, wait)

    def powerOff(self, id: int, wait: int = 0):
        return _libwdactions.powerOff(self.watchdog, id, wait)

    def kickDog(self, id: int, wait: int = 0):
        return _libwdactions.kickDog(self.watchdog, id, wait)


if __name__ == "__main__":
    # execute only if run as a script
    print("hello")

    wdaddr = c_int(0x08)
    watchdog = PiWatchDog(wdaddr)

    watchdog.fanOn(0, 0)

    sleep(5)

    watchdog.fanOff(0, 0)
