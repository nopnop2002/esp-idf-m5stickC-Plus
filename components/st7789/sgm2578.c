#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "driver/gpio.h"

#include "sgm2578.h"

// VLED is supplied by SGM2578
void sgm2578_Enable(int gpio) {
	gpio_reset_pin( gpio );
	gpio_set_direction( gpio, GPIO_MODE_OUTPUT );
	gpio_set_level( gpio, 1 );
	vTaskDelay(100);
	gpio_set_level( gpio, 0 );
	vTaskDelay(100);
	gpio_set_level( gpio, 1 );

	return;
}
