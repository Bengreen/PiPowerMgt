#ifndef PAYLOAD_H
#define PAYLOAD_H
#include <stdint.h>

typedef enum
{
    NONE,
    COMMAND_POWER_ON,
    COMMAND_POWER_OFF,
    COMMAND_FAN_OFF,
    COMMAND_FAN_ON,
    CONFIG_TIMEOUT,
    CONFIG_FAN,
    CONFIG_POWER,
    CONFIG_CYCLETIME,
    WATCHDOG_KICK,
    WATCHDOG_ON,
    WATCHDOG_OFF,
} action_t;

union configParams_t
{
    uint16_t timeout;
    uint16_t cycleTime;
    uint8_t fanIO;
    uint8_t powerIO;
};

struct config_t
{
    uint8_t id;
    configParams_t params;
};

struct watchdog_t
{
    uint8_t id;
};

struct command_t
{
    uint8_t id;
};

union taskOption_t
{
    command_t command;
    config_t config;
    watchdog_t watchdog;
};

struct task_t
{
    uint8_t action;
    uint16_t wait;
    union taskOption_t options;
};

/** Future task
 */
struct fTask_t
{
    unsigned long time;
    task_t task;
};

#endif