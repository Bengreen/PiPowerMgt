#ifndef PAYLOAD_H
#define PAYLOAD_H
#include "tasks.h"

typedef enum
{
    TASK,
} command_t;

union payload_t
{
    task_t task;
};

struct message_t
{
    uint8_t command;
    union payload_t payload;
};

#endif