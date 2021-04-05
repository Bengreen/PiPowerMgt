#ifndef TASKS_H
#define TASKS_H
#include <stdint.h>
#include "pi.h"
#include "payload.h"

void addTask(fTask_t *tasks, int maxTasks, task_t task, unsigned long time = 0);
unsigned long processTasks(pi *pis, fTask_t *tasks, int maxTasks, unsigned long tprev);

#endif