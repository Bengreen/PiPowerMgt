#ifndef WDACTIONS_H
#define WDACTIONS_H

#include "../arduino/watchdog/payload.h"

extern "C"
{
    typedef int watchdogId_t;

    watchdogId_t createWatchdog(int watchdogAddress);
    int fanOn(watchdogId_t watchdog, uint8_t id, uint16_t wait);
    int fanOff(watchdogId_t watchdog, uint8_t id, uint16_t wait);
    int powerOn(watchdogId_t watchdog, uint8_t id, uint16_t wait);
    int powerOff(watchdogId_t watchdog, uint8_t id, uint16_t wait);
    int configTimeout(watchdogId_t watchdog, uint8_t id, uint16_t timeout, uint16_t wait);
    int configCycleTime(watchdogId_t watchdog, uint8_t id, uint16_t cycleTime, uint16_t wait);
    int configFanIO(watchdogId_t watchdog, uint8_t id, uint8_t io, uint16_t wait);
    int configPowerIO(watchdogId_t watchdog, uint8_t id, uint8_t io, uint16_t wait);
};
#endif