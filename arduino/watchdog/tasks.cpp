#include "tasks.h"
#include "pi.h"
#include <HardwareSerial.h>
extern HardwareSerial Serial;

void addAction(task_t *tasklist, int maxImmediateActions, int id, action_t action)
{
    for (int index = 0; index < maxImmediateActions; ++index)
    {
        Serial.println(index);
        if (tasklist[index].action == action_t::NONE)
        {
            tasklist[index].action = action;
            tasklist[index].id = id;
            Serial.print(index);
            Serial.print(" <- [");
            Serial.print(id);
            Serial.print("] = ");
            Serial.println(int(action));

            break;
        }
    }
}

void processTasks(pi *pis, task_t *tasklist, int count)
{
    for (int index = 0; index < count; ++index)
    {
        switch (tasklist[index].action)
        {
        case action_t::NONE:
            break;
        case action_t::POWER_ON:
        case action_t::POWER_OFF:
        case action_t::FAN_ON:
        case action_t::FAN_OFF:
            Serial.print(tasklist[index].id);
            Serial.print(" -> ");
            Serial.println(int(tasklist[index].action));
            piAction(pis[tasklist[index].id], tasklist[index].action);
            break;
        default:
            Serial.print(index);
            Serial.print(" ");
            Serial.println("UNKNOWN");
            break;
        }
        tasklist[index].action = action_t::NONE;
    }
}
