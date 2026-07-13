#include <stdio.h>
#include <stdbool.h>
#include "event_dispatcher.h"
#include "state_machine.h"
#include "logger.h"
#include "statistics_manager.h"

static bool start_handler(void);
static bool stop_handler(void);
static bool status_handler(void);
static bool help_handler(void);
static bool error_handler(void);
static bool reset_handler(void);
static bool timeout_handler(void);

typedef struct
{
    EventType event;
    bool (*handler)(void);
} EventEntry;

static EventEntry event_table[] =
{
    { EVENT_START,  start_handler },
    { EVENT_STOP,   stop_handler },
    { EVENT_STATUS, status_handler },
    { EVENT_HELP,   help_handler },
	{ EVENT_ERROR, error_handler },
	{ EVENT_RESET, reset_handler },
	{ EVENT_TIMEOUT, timeout_handler }
};

void dispatch_event(EventType event)
{
    int len = sizeof(event_table) / sizeof(event_table[0]);

    for (int i = 0; i < len; i++)
    {
        if (event == event_table[i].event)
        {
            statistics_manager_record_event(event);
            bool state_changed = event_table[i].handler();

            if (state_changed)
            {
                device_controller_apply_state(
                    state_machine_get_state()
                );
            }

            return;
        }
    }

    log_error("Unknown event");
}

static bool start_handler(void)
{
    bool success = state_machine_set_state(STATE_RUNNING);

    if (success)
    {
        log_info("Device Started");
    }
    else
    {
        log_error("Invalid state transition: cannot start device");
    }

    return success;
}

static bool stop_handler(void)
{
    bool success = state_machine_set_state(STATE_IDLE);

    if (success)
    {
        log_info("Device Stopped");
    }
    else
    {
        log_error("Invalid state transition: cannot stop device");
    }

    return success;
}

static bool status_handler(void)
{
    SystemState state = state_machine_get_state();

    printf("Current State: %s\n",
           state_machine_get_state_name(state));

    statistics_manager_print();

    return false;
}

static bool help_handler(void)
{
    log_info("Available commands: start, stop, status, help");

	return false;
}

static bool error_handler(void)
{
    bool success = state_machine_set_state(STATE_ERROR);

    if (success)
    {
        log_error("Device entered ERROR state");
    }
    else
    {
        log_error("Invalid state transition: cannot enter ERROR state");
    }

    return success;
}

static bool reset_handler(void)
{
    bool success = state_machine_reset();

    if (success)
    {
        log_info("Device Reset");
    }
    else
    {
        log_error("Device Reset Failed");
    }

    return success;
}

static bool timeout_handler(void)
{
    bool success = state_machine_set_state(STATE_IDLE);

    if (success)
    {
        log_info("Timer expired - device returned to IDLE");
    }
    else
    {
        log_error("Timer expired but state transition was rejected");
    }

    return success;
}
