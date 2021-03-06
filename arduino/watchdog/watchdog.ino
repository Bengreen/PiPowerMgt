#include <Wire.h>
#include "tasks.h"
#include <Arduino.h>
#include "pi.h"
#include "payload.h"

#include <HardwareSerial.h>
extern HardwareSerial Serial;

struct ftask
{
    task_t futureTask;
    int time;
};

const int maxImmediateActions(16);
const int maxFutureActions(16);

task_t immediate[maxImmediateActions] = {{action_t::NONE, 0}};
task_t ftask[maxFutureActions];

const int maxPis = 4;
pi pis[maxPis] = {
    {13, 12, 0, false, powerState_t::POWER_OFF},
    {11, 10, 0, false, powerState_t::POWER_OFF},
    {9, 8, 0, false, powerState_t::POWER_OFF},
    {7, 6, 0, false, powerState_t::POWER_OFF}};

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    while (Wire.available())
    {                         // loop through all but the last
        char c = Wire.read(); // receive byte as a character
        Serial.print(c, HEX); // print the character
    }
    Serial.println("");
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
    Wire.write("hello "); // respond with message of 6 bytes
                          // as expected by master
}

void setup()
{
    Serial.begin(9600); // start serial for output

    for (int index = 0; index < maxPis; ++index)
    {
        initPi(pis[index]);

        Serial.print(index);
        Serial.print(" ");
        statusDump(pis[index]);
        Serial.println("");
    }
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    Wire.onRequest(requestEvent); // register event

    // processTasks(immediate, maxImmediateActions);

    // addAction(immediate, 1, maxImmediateActions, action_t::POWER_ON);
    // processTasks(immediate, maxImmediateActions);

    // processTasks(immediate, maxImmediateActions);

    // addAction(immediate, 4, maxImmediateActions, action_t::FAN_ON);
    // addAction(immediate, 2, maxImmediateActions, action_t::POWER_ON);
    // addAction(immediate, 3, maxImmediateActions, action_t::FAN_OFF);
    // processTasks(immediate, maxImmediateActions);

    Serial.print("message is ");
    Serial.println(sizeof(message_t));

    addAction(immediate, maxImmediateActions, 0, action_t::FAN_OFF);
}

void loop()
{
    delay(1000);
    processTasks(pis, immediate, maxImmediateActions);
}
