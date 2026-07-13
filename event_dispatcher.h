#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "event_queue.h"
#include "state_machine.h"
#include "device_controller.h"

void dispatch_event(EventType event);

#endif