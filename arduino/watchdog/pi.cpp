#include "pi.h"
#include <Arduino.h>
#include "tasks.h"

#include <HardwareSerial.h>
extern HardwareSerial Serial;

void statusDump(const pi &myPi)
{

    Serial.print(myPi.fanIO);
    Serial.print(" ");
    Serial.print(myPi.powerIO);
    Serial.print(" ");
    Serial.print(myPi.watchdogDeadline);
    Serial.print(" ");
    Serial.print(myPi.watchdog ? "WD" : "  ");
    Serial.print(" ");
    Serial.print("<POWERSTATE>");
}

void piAction(pi &myPi, action_t action)
{
    switch (action)
    {
    case action_t::POWER_ON:
        powerOn(myPi);
        break;
    case action_t::POWER_OFF:
        powerOff(myPi);
        break;
    case action_t::FAN_ON:
        fanOn(myPi);
        break;
    case action_t::FAN_OFF:
        fanOff(myPi);
        break;
    default:
        break;
    }
}

void fanOn(pi &myPi)
{
    digitalWrite(myPi.fanIO, HIGH);
}
void fanOff(pi &myPi)
{
    digitalWrite(myPi.fanIO, LOW);
}
void powerOn(pi &myPi)
{
    digitalWrite(myPi.powerIO, HIGH);
}
void powerOff(pi &myPi)
{
    digitalWrite(myPi.powerIO, LOW);
}

void initPi(pi &myPi)
{
    // Turn fan on and Pi off
    pinMode(myPi.powerIO, OUTPUT);
    fanOn(myPi);

    pinMode(myPi.fanIO, OUTPUT);
    powerOff(myPi);
}
