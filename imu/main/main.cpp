#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "parameter.h"

static const char *TAG = "MAIN";

QueueHandle_t xQueueImu;

extern "C" {
	void app_main(void);
	void i2c_master_init();
	void tft(void *pvParameters);
	void buttonA(void *pvParameters);
	void buttonB(void *pvParameters);
}

void mpu6050(void *pvParameters);

void app_main(void)
{
	// Initialize i2c
	i2c_master_init();

	// Create Queue
	xQueueImu = xQueueCreate(10, sizeof(MOTION6_t));
	configASSERT( xQueueImu );

	// Start tft task
	xTaskCreate(&tft, "TFT", 1024*6, NULL, 5, NULL);
	vTaskDelay(100);

	// Start button task
	xTaskCreate(&buttonA, "BUTTON", 1024*2, NULL, 5, NULL);
	vTaskDelay(100);

	// Start imu task
	xTaskCreate(&mpu6050, "IMU", 1024*8, NULL, 5, NULL);
	vTaskDelay(100);
}
