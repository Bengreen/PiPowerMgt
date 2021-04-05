#include "pi.h"
#include <Arduino.h>
#include "payload.h"

#include <HardwareSerial.h>
extern HardwareSerial Serial;

void statusDump(const pi &myPi)
{

    Serial.print(myPi.fanIO);
    Serial.print(" ");
    Serial.print(myPi.powerIO);
    Serial.print(" ");
    Serial.print(myPi.timeout);
    Serial.print(" ");
    Serial.print(myPi.cycleTime);
    Serial.print(" ");
    Serial.print(myPi.watchdog ? "WD" : "  ");
    Serial.print(" ");
    Serial.print("<POWERSTATE>");
}

void piAction(pi &myPi, action_t action)
{
    switch (action)
    {
    case action_t::COMMAND_POWER_ON:
        powerOn(myPi);
        break;
    case action_t::COMMAND_POWER_OFF:
        powerOff(myPi);
        break;
    case action_t::COMMAND_FAN_ON:
        fanOn(myPi);
        break;
    case action_t::COMMAND_FAN_OFF:
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

void config(pi &myPi, task_t &task)
{
    switch (task.action)
    {
    case action_t::CONFIG_FAN:
        myPi.fanIO = task.options.config.params.fanIO;
        break;
    case action_t::CONFIG_POWER:
        myPi.powerIO = task.options.config.params.powerIO;
        break;
    case action_t::CONFIG_TIMEOUT:
        myPi.timeout = task.options.config.params.timeout;
        break;
    case action_t::CONFIG_CYCLETIME:
        myPi.cycleTime = task.options.config.params.cycleTime;
        break;
    }
}

void watchDog(pi &myPi, watchdog_t &watchdog)
{
}
