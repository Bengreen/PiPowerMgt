#ifndef TASKS_H
#define TASKS_H
#include "pi.h"
#include "actions.h"

struct task_t
{
    action_t action;
    int id;
};

void processTasks(pi *pis, task_t *tasklist, int count);
void addAction(task_t *tasklist, int maxImmediateActions, int id, action_t action);

#endif