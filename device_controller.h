#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <stdio.h>
#include "state_machine.h"
#include "led_driver.h"

void device_controller_init(void);

void device_controller_apply_state(SystemState state);

void device_controller_print_status(void);

#endif