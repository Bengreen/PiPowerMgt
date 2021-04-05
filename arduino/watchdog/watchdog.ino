#include <Wire.h>
#include "tasks.h"
#include <Arduino.h>
#include "pi.h"
#include "payload.h"

#include <HardwareSerial.h>
extern HardwareSerial Serial;

const int watchdogAddr = 0x08;

// static const int maxImmediateCommands(16);
static const int maxTasks(16);

// command_t immediate[maxImmediateCommands] = {{action_t::NONE, 0}};
fTask_t tasks[maxTasks] = {{.time = 0UL, .task = {.action = action_t::NONE}}};
unsigned long tprev = 0UL;

char i2cBuffer[BUFFER_LENGTH];

const int maxPis = 4;
pi pis[maxPis] = {
    {13, 12, 0, 30, false, powerState_t::POWER_OFF},
    {11, 10, 0, 30, false, powerState_t::POWER_OFF},
    {9, 8, 0, 30, false, powerState_t::POWER_OFF},
    {7, 6, 0, 30, false, powerState_t::POWER_OFF}};

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    int index = 0;

    while (Wire.available())
    {
        char c = Wire.read(); // receive byte as a character
        i2cBuffer[index] = c;

        Serial.print(c, HEX); // print the character
        Serial.print(" ");
        //Serial.println((int)&i2cBuffer[index]);
        ++index;
    }
    Serial.println("");

    task_t *myMessage = (task_t *)i2cBuffer;

    Serial.print((int)myMessage);
    Serial.print(":");
    // Serial.println((int)i2cBuffer);

    Serial.print("Task is ");
    Serial.println((int)(myMessage->action));
    Serial.print("Wait is ");
    Serial.println((int)myMessage->wait);

    addTask(tasks, maxTasks, *myMessage, myMessage->wait);
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

    Serial.print("sizeof(task_t) = ");
    Serial.println((int)sizeof(task_t));

    for (int index = 0; index < maxPis; ++index)
    {
        initPi(pis[index]);

        Serial.print(index);
        Serial.print(" ");
        statusDump(pis[index]);
        Serial.println("");
        addTask(tasks, maxTasks, {.action = action_t::COMMAND_FAN_ON, .wait = 0, .options = {.command = {.id = uint8_t(index)}}}, 1);
    }

    Wire.begin(watchdogAddr);     // join i2c bus with address
    Wire.onReceive(receiveEvent); // register event
    Wire.onRequest(requestEvent); // register event
}

void loop()
{
    delay(1000);
    tprev = processTasks(pis, tasks, maxTasks, tprev);
}
