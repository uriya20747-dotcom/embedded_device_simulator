#include <stdbool.h>
#include "timer_manager.h"
#include "event_queue.h"

static bool timer_active;
static unsigned int remaining_ticks;

void timer_manager_init(void)
{
    timer_active = false;
    remaining_ticks = 0;
}

void timer_manager_start(unsigned int duration_seconds)
{
    remaining_ticks = duration_seconds;
    timer_active = true;
}

void timer_manager_tick(void)
{
    if (!timer_active)
    {
        return;
    }

    if (remaining_ticks > 0)
    {
        remaining_ticks--;
    }

    if (remaining_ticks == 0)
    {
        timer_active = false;
        event_queue_push(EVENT_TIMEOUT);
    }
}