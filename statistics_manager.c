#include <stdio.h>
#include "statistics_manager.h"



static unsigned int event_counters[EVENT_COUNT];

typedef struct
{
    EventType event;
    const char *name;
} EventNameEntry;

static const EventNameEntry event_names[] =
{
    { EVENT_START,   "START" },
    { EVENT_STOP,    "STOP" },
    { EVENT_STATUS,  "STATUS" },
    { EVENT_HELP,    "HELP" },
    { EVENT_ERROR,   "ERROR" },
    { EVENT_RESET,   "RESET" },
    { EVENT_TIMEOUT, "TIMEOUT" }
};

void statistics_manager_init(void)
{
    for (int i = 0; i < EVENT_COUNT; i++)
    {
        event_counters[i] = 0;
    }
}

void statistics_manager_record_event(EventType event)
{
    if (event >= 0 && event < EVENT_COUNT)
    {
        event_counters[event]++;
    }
}

void statistics_manager_print(void)
{
    int len = sizeof(event_names) / sizeof(event_names[0]);

    printf("\n===== SYSTEM STATS =====\n");

    for (int i = 0; i < len; i++)
    {
        EventType event = event_names[i].event;

        printf("%-8s : %u\n",
               event_names[i].name,
               event_counters[event]);
    }

    printf("========================\n");
}