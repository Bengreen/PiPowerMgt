
#include "../arduino/watchdog/payload.h"
#include "wdactions.h"
#include <wiringPiI2C.h>
#include <unistd.h>

extern "C"
{

    watchdogId_t createWatchdog(int watchdogAddress)
    {
        return wiringPiI2CSetup(watchdogAddress);
    }

    // int sendMessage(watchdogId_t watchdog, task_t message)
    // {
    //     return write(watchdog, &message, sizeof(task_t));
    // }
    // int fanOnFake(uint8_t id, uint16_t wait)
    // {
    //     task_t message = {
    //         .action = action_t::COMMAND_FAN_ON,
    //         .wait = wait,
    //         .options = {.command = {.id = id}}};
    //     return 0;
    // }
    int fanOn(watchdogId_t watchdog, uint8_t id, uint16_t wait)
    {
        task_t message = {
            .action = action_t::COMMAND_FAN_ON,
            .wait = wait,
            .options = {.command = {.id = id}}};
        return write(watchdog, &message, sizeof(task_t));
    }

    int fanOff(watchdogId_t watchdog, uint8_t id, uint16_t wait)
    {
        task_t message = {
            .action = action_t::COMMAND_FAN_OFF,
            .wait = wait,
            .options = {.command = {.id = id}}};
        return write(watchdog, &message, sizeof(task_t));
    }
    int powerOn(watchdogId_t watchdog, uint8_t id, uint16_t wait)
    {
        task_t message = {
            .action = action_t::COMMAND_POWER_ON,
            .wait = wait,
            .options = {.command = {.id = id}}};
        return write(watchdog, &message, sizeof(task_t));
    }
    int powerOff(watchdogId_t watchdog, uint8_t id, uint16_t wait)
    {
        task_t message = {
            .action = action_t::COMMAND_POWER_ON,
            .wait = wait,
            .options = {.command = {.id = id}}};
        return write(watchdog, &message, sizeof(task_t));
    }
    int kickDog(watchdogId_t watchdog, uint8_t id, uint16_t wait)
    {
        task_t message = {
            .action = action_t::WATCHDOG_KICK,
            .wait = wait,
            .options = {.watchdog = {.id = id}}};
        return write(watchdog, &message, sizeof(task_t));
    }
    int configTimeout(watchdogId_t watchdog, uint8_t id, uint16_t timeout, uint16_t wait)
    {
        task_t message = {
            .action = action_t::CONFIG_TIMEOUT,
            .wait = wait,
            .options = {
                .config = {
                    .id = id,
                    .params = {.timeout = timeout},

                },
            },
        };
        return write(watchdog, &message, sizeof(task_t));
    }
    int configCycleTime(watchdogId_t watchdog, uint8_t id, uint16_t cycleTime, uint16_t wait)
    {
        task_t message = {
            .action = action_t::CONFIG_CYCLETIME,
            .wait = wait,
            .options = {
                .config = {
                    .id = id,
                    .params = {.cycleTime = cycleTime},

                },
            },
        };
        return write(watchdog, &message, sizeof(task_t));
    }
    int configFanIO(watchdogId_t watchdog, uint8_t id, uint8_t io, uint16_t wait)
    {
        task_t message = {
            .action = action_t::CONFIG_FAN,
            .wait = wait,
            .options = {
                .config = {
                    .id = id,
                    .params = {.fanIO = io},

                },
            },
        };
        return write(watchdog, &message, sizeof(task_t));
    }
    int configPowerIO(watchdogId_t watchdog, uint8_t id, uint8_t io, uint16_t wait)
    {
        task_t message = {
            .action = action_t::CONFIG_POWER,
            .wait = wait,
            .options = {
                .config = {
                    .id = id,
                    .params = {.powerIO = io},

                },
            },
        };
        return write(watchdog, &message, sizeof(task_t));
    }
};