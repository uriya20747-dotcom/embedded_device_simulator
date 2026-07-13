#include "device_controller.h"
#include "led_driver.h"

void device_controller_init(void)
{
    led_driver_init();
}

void device_controller_apply_state(SystemState state)
{
    switch (state)
    {
        case STATE_IDLE:
            led_driver_off();
            break;

        case STATE_RUNNING:
            led_driver_on();
            break;
			
		case STATE_ERROR:
			led_driver_blink_fast();
			break;

        default:
            led_driver_off();
            break;
    }
}