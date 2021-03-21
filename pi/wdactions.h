#ifndef WDACTIONS_H
#define WDACTIONS_H

#include "../arduino/watchdog/payload.h"

extern "C"
{

    typedef int watchdog_t;

    watchdog_t createWatchdog(int watchdogAddress);
    int sendMessage(watchdog_t watchdog, message_t message);
    message_t fanOnMessage(uint8_t id);
    message_t fanOffMessage(uint8_t id);
    message_t powerOnMessage(uint8_t id);
    message_t powerOffMessage(uint8_t id);
};
#endif