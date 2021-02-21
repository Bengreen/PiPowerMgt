#ifndef PI_H
#define PI_H
#include "actions.h"

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
    int watchdogDeadline;
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

#endif