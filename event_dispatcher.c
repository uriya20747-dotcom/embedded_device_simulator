#include <stdio.h>
#include "event_dispatcher.h"
#include "state_machine.h"
#include "logger.h"

static void start_handler(void);
static void stop_handler(void);
static void status_handler(void);
static void help_handler(void);

typedef struct
{
    EventType event;
    void (*handler)(void);
} EventEntry;

static EventEntry event_table[] =
{
    { EVENT_START,  start_handler },
    { EVENT_STOP,   stop_handler },
    { EVENT_STATUS, status_handler },
    { EVENT_HELP,   help_handler }
};

void dispatch_event(EventType event)
{
    int len = sizeof(event_table) / sizeof(event_table[0]);

    for(int i = 0; i < len; i++)
    {
        if(event == event_table[i].event)
        {
            event_table[i].handler();
            return;
        }
    }

    log_error("Unknown event");
}

static void start_handler(void)
{
    state_machine_set_state(STATE_RUNNING);
    log_info("Device Started");
}

static void stop_handler(void)
{
    state_machine_set_state(STATE_IDLE);
    log_info("Device Stopped");
}

static void status_handler(void)
{
    SystemState state = state_machine_get_state();

    printf("Current State: %s\n",
           state_machine_get_state_name(state));
}

static void help_handler(void)
{
    log_info("Available commands: start, stop, status, help");
}