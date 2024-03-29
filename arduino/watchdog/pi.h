#ifndef PI_H
#define PI_H
#include "payload.h"

enum class powerState_t
{
    POWER_OFF,
    POWER_ON,
    WAIT_AND_POWER_OFF,
    WAIT_AND_POWER_ON,
};

struct pi
{
    int fanIO;
    int powerIO;
    int timeout;
    int cycleTime;
    bool watchdog;
    powerState_t powerState;
};

void statusDump(const pi &myPi);
void initPi(pi &myPi);
void fanOn(pi &myPi);
void fanOff(pi &myPi);
void powerOn(pi &myPi);
void powerOff(pi &myPi);
void piAction(pi &myPi, action_t action);

void config(pi &myPi, config_t &config);
void watchDog(pi &myPi, watchdog_t &watchdog);
#endif