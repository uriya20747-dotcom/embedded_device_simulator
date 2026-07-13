#include "state_machine.h"

static SystemState current_state;

void state_machine_init(void)
{
    current_state = STATE_IDLE;
}

bool state_machine_set_state(SystemState new_state)
{
    if (current_state == STATE_ERROR)
    {
        return false;
    }

    current_state = new_state;
    return true;
}

SystemState state_machine_get_state(void)
{
    return current_state;
}

bool state_machine_reset(void)
{
    current_state = STATE_IDLE;
    return true;
}

const char* state_machine_get_state_name(SystemState state)
{
    switch(state)
    {
        case STATE_IDLE:
            return "IDLE";

        case STATE_RUNNING:
            return "RUNNING";

        case STATE_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}