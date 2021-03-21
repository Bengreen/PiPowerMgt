
#include "../arduino/watchdog/payload.h"
#include "wdactions.h"
#include <wiringPiI2C.h>
#include <unistd.h>

extern "C"
{

    watchdog_t createWatchdog(int watchdogAddress)
    {
        return wiringPiI2CSetup(watchdogAddress);
    }

    int sendMessage(watchdog_t watchdog, message_t message)
    {
        return write(watchdog, &message, sizeof(message_t));
    }

    message_t fanOnMessage(uint8_t id)
    {
        message_t message = {
            .command = command_t::TASK,
            .payload = {
                .task = {
                    .action = action_t::FAN_ON,
                    .id = id}}};
        return message;
    }

    message_t fanOffMessage(uint8_t id)
    {
        message_t message = {
            .command = command_t::TASK,
            .payload = {
                .task = {
                    .action = action_t::FAN_OFF,
                    .id = id}}};
        return message;
    }
    message_t powerOnMessage(uint8_t id)
    {
        message_t message = {
            .command = command_t::TASK,
            .payload = {
                .task = {
                    .action = action_t::POWER_ON,
                    .id = id}}};
        return message;
    }
    message_t powerOffMessage(uint8_t id)
    {
        message_t message = {
            .command = command_t::TASK,
            .payload = {
                .task = {
                    .action = action_t::POWER_OFF,
                    .id = id}}};
        return message;
    }
    message_t kickDogMessage(uint8_t id)
    {
        message_t message = {
            .command = command_t::KICK,
            .payload = {
                .kick = {
                    .id = id}}};
        return message;
    }
};