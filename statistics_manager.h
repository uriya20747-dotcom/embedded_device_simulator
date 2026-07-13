#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

#include "event_queue.h"

void statistics_manager_init(void);
void statistics_manager_record_event(EventType event);
void statistics_manager_print(void);

#endif