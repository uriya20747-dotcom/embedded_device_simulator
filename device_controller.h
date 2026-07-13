#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include "state_machine.h"

void device_controller_init(void);
void device_controller_apply_state(SystemState state);

#endif