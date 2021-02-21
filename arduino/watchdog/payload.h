#ifndef PAYLOAD_H
#define PAYLOAD_H
#include "tasks.h"

enum class command_t
{
    TASK,
};

union payload_t
{
    task_t task;
};

struct
{
    command_t command;
    union payload_t payload;
} message_t;

#endif