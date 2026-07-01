#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdbool.h>

typedef enum {
    EVENT_START,
    EVENT_STOP,
    EVENT_STATUS,
    EVENT_HELP,
    EVENT_UNKNOWN
} EventType;

void event_queue_init(void);

bool event_queue_push(EventType event);
bool event_queue_pop(EventType *event);

bool event_queue_is_empty(void);
bool event_queue_is_full(void);
int event_queue_size(void);

#endif