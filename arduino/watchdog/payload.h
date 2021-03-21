#ifndef PAYLOAD_H
#define PAYLOAD_H
#include "tasks.h"
#include "kicks.h"

typedef enum
{
    TASK,
    KICK,
} command_t;

union payload_t
{
    task_t task;
    kick_t kick;
};

struct message_t
{
    uint8_t command;
    union payload_t payload;
};

#endif