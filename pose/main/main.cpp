#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "I2Cdev.h"
#include "parameter.h"

#define SYS_SDA 21
#define SYS_SCL 22

static const char *TAG = "MAIN";

QueueHandle_t xQueueImu;

extern "C" {
#if CONFIG_M5STICK_C_PLUS
    void AXP192_AddDevice(i2c_master_bus_handle_t bus_handle, uint16_t devAddr);
    void AXP192_PowerOn(void);
    void AXP192_ScreenBreath(uint8_t brightness);
#endif
#if CONFIG_M5STICK_C_PLUS2
    void sgm2578_Enable(int gpio);
#endif
	void listSPIFFS(const char * path);
	esp_err_t mountSPIFFS(const char * path, const char * label, int max_files);
	void tft(void *pvParameters);
	void buttonA(void *pvParameters);
	void buttonB(void *pvParameters);
	void app_main(void);
}

void mpu6050(void *pvParameters);

void app_main(void)
{
#if CONFIG_M5STICK_C_PLUS
    // Initialize i2c
    i2c_master_bus_handle_t bus_handle = I2Cdev::initialize(SYS_SDA, SYS_SCL);
    // Power on the AXP192
    #define AXP192_I2C_ADDRESS 0x34
    AXP192_AddDevice(bus_handle, AXP192_I2C_ADDRESS);
    AXP192_PowerOn();
    AXP192_ScreenBreath(11);
#endif

#if CONFIG_M5STICK_C_PLUS2
    // Initialize i2c
    I2Cdev::initialize(SYS_SDA, SYS_SCL);
    // Power hold the SGM2578
    #define POWER_HOLD_GPIO (gpio_num_t)4
    gpio_reset_pin( POWER_HOLD_GPIO );
    gpio_set_direction( POWER_HOLD_GPIO, GPIO_MODE_OUTPUT );
    gpio_set_level( POWER_HOLD_GPIO, 1 );
    // Enable SGM2578. VLED is supplied by SGM2578
    #define SGM2578_ENABLE_GPIO (gpio_num_t)27
    sgm2578_Enable(SGM2578_ENABLE_GPIO);
#endif

	// Mount SPIFFS File System on FLASH
	ESP_LOGI(TAG, "Initializing SPIFFS");
	ESP_ERROR_CHECK(mountSPIFFS("/fonts", "storage1", 8));
	listSPIFFS("/fonts");

	// Create Queue
	xQueueImu = xQueueCreate(10, sizeof(MOTION6_t));
	configASSERT( xQueueImu );

	// Start tft task
	xTaskCreate(&tft, "TFT", 1024*6, NULL, 5, NULL);
	vTaskDelay(100);

	// Start imu task
	xTaskCreate(&mpu6050, "IMU", 1024*8, NULL, 5, NULL);
	vTaskDelay(100);
}
