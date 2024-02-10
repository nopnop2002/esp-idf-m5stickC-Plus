#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "parameter.h"

#if CONFIG_M5STICK_C_PLUS
#define GPIO_INPUT_A GPIO_NUM_37
#define GPIO_INPUT_B GPIO_NUM_39
#endif

#if CONFIG_M5STICK_C_PLUS2
#define GPIO_INPUT_A GPIO_NUM_37
#define GPIO_INPUT_B GPIO_NUM_39
#endif

extern QueueHandle_t xQueueImu;

static const char *TAG = "BUTTON";

void buttonA(void *pvParameters)
{
	ESP_LOGI(pcTaskGetName(0), "Start");
	MOTION6_t motion6;
	motion6.sender = SENDER_BUTTON;
	
	// set the GPIO as a input
	gpio_reset_pin(GPIO_INPUT_A);
	gpio_set_direction(GPIO_INPUT_A, GPIO_MODE_DEF_INPUT);

	while(1) {
		int level = gpio_get_level(GPIO_INPUT_A);
		if (level == 0) {
			ESP_LOGI(pcTaskGetName(0), "Push Button");
			while(1) {
				level = gpio_get_level(GPIO_INPUT_A);
				if (level == 1) break;
				vTaskDelay(1);
			}
			xQueueSend(xQueueImu, &motion6, 100);
		}
		vTaskDelay(1);
	}
}

void buttonB(void *pvParameters)
{
	ESP_LOGI(pcTaskGetName(0), "Start");
	MOTION6_t motion6;
	motion6.sender = SENDER_BUTTON;

	// set the GPIO as a input
	gpio_reset_pin(GPIO_INPUT_B);
	gpio_set_direction(GPIO_INPUT_B, GPIO_MODE_DEF_INPUT);

	while(1) {
		int level = gpio_get_level(GPIO_INPUT_A);
		if (level == 0) {
			ESP_LOGI(pcTaskGetName(0), "Push Button");
			while(1) {
				level = gpio_get_level(GPIO_INPUT_A);
				if (level == 1) break;
				vTaskDelay(1);
			}
			xQueueSend(xQueueImu, &motion6, 100);
		}
		vTaskDelay(1);
	}
}
