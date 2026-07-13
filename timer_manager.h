#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

void timer_manager_init(void);
void timer_manager_start(unsigned int duration_seconds);
void timer_manager_tick(void);

#endif