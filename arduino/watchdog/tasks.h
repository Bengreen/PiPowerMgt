#ifndef TASKS_H
#define TASKS_H
#include <stdint.h>
#include "pi.h"
#include "actions.h"

struct task_t
{
    uint8_t action;
    uint8_t id;
};

void processTasks(pi *pis, task_t *tasklist, int count);
void addAction(task_t *tasklist, int maxImmediateActions, int id, action_t action);

#endif