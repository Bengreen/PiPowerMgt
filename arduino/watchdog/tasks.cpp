#include "tasks.h"
#include "pi.h"
#include "payload.h"
#include <HardwareSerial.h>
#include <Arduino.h>
extern HardwareSerial Serial;

void addTask(fTask_t *tasks, int maxTasks, task_t task, unsigned long time)
{
    for (int index = 0; index < maxTasks; ++index)
    {
        if (tasks[index].task.action == action_t::NONE)
        {
            tasks[index].task = task;
            Serial.print("[");
            Serial.print(index);
            Serial.print("] <- (");
            Serial.print("x");
            Serial.print(") = ");
            Serial.println(int(task.action));
            tasks[index].time = millis() + time;
            break;
        }
    }
}

unsigned long processTasks(pi *pis, fTask_t *tasks, int maxTasks, unsigned long tprev)
{
    unsigned long tnow = millis();

    for (int index = 0; index < maxTasks; ++index)
    {
        if ((tasks[index].time > tprev && tasks[index].time <= tnow) || (tnow < tprev && (tasks[index].time > tprev || tasks[index].time < tnow)))
        {
            switch (tasks[index].task.action)
            {
            case action_t::NONE:
                break;
            case action_t::COMMAND_POWER_ON:
            case action_t::COMMAND_POWER_OFF:
            case action_t::COMMAND_FAN_ON:
            case action_t::COMMAND_FAN_OFF:
                Serial.print("[");
                Serial.print(index);
                Serial.print("] = (");
                Serial.print(tasks[index].task.options.command.id);
                Serial.print(") -> ACTION - ");
                Serial.println(int(tasks[index].task.action));
                piAction(pis[tasks[index].task.options.command.id], action_t(tasks[index].task.action));
                break;
            default:
                Serial.println("DONT KNOW HOW TO DEAL WITH THIS TASK");
                Serial.print("[");
                Serial.print(index);
                Serial.print("] = (");
                Serial.print(tasks[index].task.options.command.id);
                Serial.print(") -> ");
                Serial.println(int(tasks[index].task.action));
                break;
            }
            //Clear tasks regardless of success
            tasks[index].task.action = action_t::NONE;
        }
    }
    return tnow;
}
