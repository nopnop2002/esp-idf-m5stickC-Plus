#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "axp192.h"
#include "sgm2578.h"
#include "st7789.h"
#include "fontx.h"
#include "parameter.h"

extern QueueHandle_t xQueueImu;

// M5stickC-Plus stuff
#if CONFIG_M5STICK_C_PLUS
#define CONFIG_WIDTH 135
#define CONFIG_HEIGHT 240
#define CONFIG_MOSI_GPIO 15
#define CONFIG_SCLK_GPIO 13
#define CONFIG_CS_GPIO 5 
#define CONFIG_DC_GPIO 23
#define CONFIG_RESET_GPIO 18
#define CONFIG_BL_GPIO -1
#define CONFIG_LED_GPIO 10
#define CONFIG_OFFSETX 52
#define CONFIG_OFFSETY 40
#endif

// M5stickC-Plus2 stuff
#if CONFIG_M5STICK_C_PLUS2
#define CONFIG_WIDTH 135
#define CONFIG_HEIGHT 240
#define CONFIG_MOSI_GPIO 15
#define CONFIG_SCLK_GPIO 13
#define CONFIG_CS_GPIO 5 
#define CONFIG_DC_GPIO 14
#define CONFIG_RESET_GPIO 12
#define CONFIG_BL_GPIO -1
#define CONFIG_LED_GPIO 19
#define CONFIG_OFFSETX 52
#define CONFIG_OFFSETY 40
#endif

static const char *TAG = "TFT";

void tft(void *pvParameters)
{
	ESP_LOGI(TAG, "Start");
#if CONFIG_M5STICK_C_PLUS
	// power on
	AXP192_PowerOn();
	AXP192_ScreenBreath(11);
#endif

#if CONFIG_M5STICK_C_PLUS2
	// power hold
	#define POWER_HOLD_GPIO 4
	gpio_reset_pin( POWER_HOLD_GPIO );
	gpio_set_direction( POWER_HOLD_GPIO, GPIO_MODE_OUTPUT );
	gpio_set_level( POWER_HOLD_GPIO, 1 );
	// Enable SGM2578. VLED is supplied by SGM2578
	#define SGM2578_ENABLE_GPIO 27
	sgm2578_Enable(SGM2578_ENABLE_GPIO);
#endif

#if 0
	// set font file
	FontxFile fx16G[2];
	FontxFile fx24G[2];
	FontxFile fx32G[2];
	InitFontx(fx16G,"/fonts/ILGH16XB.FNT",""); // 8x16Dot Gothic
	InitFontx(fx24G,"/fonts/ILGH24XB.FNT",""); // 12x24Dot Gothic
	InitFontx(fx32G,"/fonts/ILGH32XB.FNT",""); // 16x32Dot Gothic

	FontxFile fx16M[2];
	FontxFile fx24M[2];
	FontxFile fx32M[2];
	InitFontx(fx16M,"/fonts/ILMH16XB.FNT",""); // 8x16Dot Mincyo
	InitFontx(fx24M,"/fonts/ILMH24XB.FNT",""); // 12x24Dot Mincyo
	InitFontx(fx32M,"/fonts/ILMH32XB.FNT",""); // 16x32Dot Mincyo
#endif
	
	TFT_t dev;
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY, false);

	int width = CONFIG_WIDTH;
	int height = CONFIG_HEIGHT;
	int xpos = width / 2.0;
	int ypos = height / 2.0; 
	float xdelta = 0.0;
	float ydelta = 0.0;
	MOTION6_t motion6;

	uint16_t colors[3];
	colors[0] = RED;
	colors[1] = CYAN;
	colors[2] = YELLOW;
	int color_index = 0;

	lcdFillScreen(&dev, BLACK);
	lcdDrawCircle(&dev, xpos, ypos, 10, colors[color_index]);
	while (1) {
		if(xQueueReceive(xQueueImu, &motion6, portMAX_DELAY)) {
			if (motion6.sender == SENDER_IMU) {
				lcdDrawCircle(&dev, xpos, ypos, 10, BLACK);
				ESP_LOGI(TAG, "acc=%f %f %f", motion6.accX, motion6.accY, motion6.accZ);
				xdelta += motion6.accX * -10.0;
				xpos += xdelta;
				ESP_LOGD(TAG, "xdelta=%f xpos=%d", xdelta, xpos);
				if(xpos>=width-10) {
					xdelta=0.0;
					xpos=width-10;
				}
				if(xpos<=10.0) {
					xdelta=0.0;
					xpos=10.0;
				}
				ydelta += motion6.accY * 10.0;
				ypos += ydelta;
				ESP_LOGD(TAG, "ydelta=%f ypos=%d", ydelta, ypos);
				if(ypos>=height-10) {
					ydelta=0.0;
					ypos=height-10;
				}
				if(ypos<=10.0) {
					ydelta=0.0;
					ypos=10.0;
				}
	
				lcdDrawCircle(&dev, xpos, ypos, 10, colors[color_index]);
			} // from imu
			if (motion6.sender == SENDER_BUTTON) {
				color_index++;
				if (color_index > 2) color_index = 0;
			} // from button
		} else {
			ESP_LOGE(TAG, "xQueueReceive fail");
			break;
		}
	} // end while

	// never reach
	while (1) {
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}
