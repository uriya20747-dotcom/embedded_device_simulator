#include <stdio.h>
#include "led_driver.h"


typedef enum
{
    LED_STATE_OFF,
    LED_STATE_ON,
    LED_STATE_BLINK_FAST,
    LED_STATE_BLINK_SLOW
} LedState;

static LedState current_led_state = LED_STATE_OFF;

void led_driver_init(void)
{
    printf("[LED DRIVER] Initialized\n");
}

void led_driver_on(void)
{
	current_led_state = LED_STATE_ON;
    printf("[LED DRIVER] LED ON\n");
}

void led_driver_off(void)
{
	current_led_state = LED_STATE_OFF;
    printf("[LED DRIVER] LED OFF\n");
}

void led_driver_blink_slow(void)
{
	current_led_state = LED_STATE_BLINK_SLOW;
    printf("[LED DRIVER] LED blinking slowly\n");
}

void led_driver_blink_fast(void)
{
	current_led_state = LED_STATE_BLINK_FAST;
    printf("[LED DRIVER] LED blinking fast\n");
}

const char* led_driver_get_state_name(void)
{
    switch (current_led_state)
    {
        case LED_STATE_OFF:
            return "OFF";

        case LED_STATE_ON:
            return "ON";

        case LED_STATE_BLINK_FAST:
            return "BLINK_FAST";

        case LED_STATE_BLINK_SLOW:
            return "BLINK_SLOW";

        default:
            return "UNKNOWN";
    }
}