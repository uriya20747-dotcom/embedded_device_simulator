#include "event_queue.h"

#define EVENT_QUEUE_CAPACITY 10

static EventType queue[EVENT_QUEUE_CAPACITY];
static int head;
static int tail;
static int count;

void event_queue_init(void)
{
    head = 0;
    tail = 0;
    count = 0;
}

bool event_queue_push(EventType event)
{
    if(event_queue_is_full())
    {
        return false;
    }

    queue[tail] = event;
    tail = (tail + 1) % EVENT_QUEUE_CAPACITY;
    count++;

    return true;
}

bool event_queue_pop(EventType *event)
{
    if(event_queue_is_empty())
    {
        return false;
    }

    *event = queue[head];
    head = (head + 1) % EVENT_QUEUE_CAPACITY;
    count--;

    return true;
}

bool event_queue_is_empty(void)
{
    return count == 0;
}

bool event_queue_is_full(void)
{
    return count == EVENT_QUEUE_CAPACITY;
}

int event_queue_size(void)
{
    return count;
}