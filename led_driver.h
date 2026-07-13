#ifndef LED_DRIVER_H
#define LED_DRIVER_H

void led_driver_init(void);
void led_driver_on(void);
void led_driver_off(void);
void led_driver_blink_slow(void);
void led_driver_blink_fast(void);
const char* led_driver_get_state_name(void);

#endif