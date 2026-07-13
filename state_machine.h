#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdbool.h>

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} SystemState;

void state_machine_init(void);
bool state_machine_reset(void);
bool state_machine_set_state(SystemState new_state);
SystemState state_machine_get_state(void);
const char* state_machine_get_state_name(SystemState state);

#endif
