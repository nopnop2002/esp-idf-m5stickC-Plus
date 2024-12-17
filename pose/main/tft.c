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

bool near_p_g(float value){
  if(8.0 < value && value < 12.0){
	return true;
  }else{
	return false;
  }
}

bool near_m_g(float value){
  if(-12.0 < value && value < -8.0){
	return true;
  }else{
	return false;
  }
}

bool near_zero(float value){
  if(-2.0 < value && value < 2.0){
	return true;
  }else{
	return false;
  }
}

typedef enum {POSE_NONE, POSE_P_X, POSE_M_X, POSE_P_Y, POSE_M_Y, POSE_P_Z, POSE_M_Z} POSE;

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
	
	TFT_t dev;
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY, false);

	int width = CONFIG_WIDTH;
	int height = CONFIG_HEIGHT;
	ESP_LOGI(TAG, "width=%d height=%d", width, height);

	// Get font width & height
    uint8_t buffer[FontxGlyphBufSize];
    uint8_t fontWidth;
    uint8_t fontHeight;
    //GetFontx(fx24G, 0, buffer, &fontWidth, &fontHeight);
    GetFontx(fx32G, 0, buffer, &fontWidth, &fontHeight);
	ESP_LOGI(TAG, "fontWidth=%d fontHeight=%d",fontWidth,fontHeight);

	// The unit of value that can be obtained by the acceleration sensor is [g], so convert it to [m/s^2].
	float accX_mpss = 0.0;
	float accY_mpss = 0.0;
	float accZ_mpss = 0.0;

	int xpos = 0;
	int ypos = 0; 
	uint8_t pose = POSE_NONE;
	uint8_t prev_pose = POSE_NONE;
	uint8_t ascii[20];
	MOTION6_t motion6;

	lcdFillScreen(&dev, BLACK);
	while (1) {
		if(xQueueReceive(xQueueImu, &motion6, portMAX_DELAY)) {
			if (motion6.sender == SENDER_IMU) {
				// Convert [g] to [m/s^2].
				accX_mpss = motion6.accX * 9.8;
				accY_mpss = motion6.accY * 9.8;
				accZ_mpss = motion6.accZ * 9.8;
				ESP_LOGD(TAG, "mpss=%f %f", motion6.accX, accX_mpss);

				// Detect current posture
				if(near_zero(accX_mpss) && near_p_g(accY_mpss) && near_zero(accZ_mpss)){
					pose = POSE_P_Y;
				}else if(near_p_g(accX_mpss) && near_zero(accY_mpss) && near_zero(accZ_mpss)){
					pose = POSE_P_X;
				}else if(near_zero(accX_mpss) && near_zero(accY_mpss) && near_p_g(accZ_mpss)){
					pose = POSE_P_Z;
				}else if(near_zero(accX_mpss) && near_m_g(accY_mpss) && near_zero(accZ_mpss)){
					pose = POSE_M_Y;
				}else if(near_m_g(accX_mpss) && near_zero(accY_mpss) && near_zero(accZ_mpss)){
					pose = POSE_M_X;
				}else if(near_zero(accX_mpss) && near_zero(accY_mpss) && near_m_g(accZ_mpss)){
					pose = POSE_M_Z;
				}else{
					pose = POSE_NONE;
				}

				ESP_LOGD(TAG, "pose=%d", pose);
				if(prev_pose == pose) continue;
				if (pose == POSE_P_X) {
					ESP_LOGI(TAG, "+X");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 1);
					strcpy((char *)ascii, "+X");
					xpos = width - fontHeight;
					ypos = (height/2) - (fontWidth/2);
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, RED);
				} else if (pose == POSE_M_X) {
					ESP_LOGI(TAG, "-X");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 3);
					strcpy((char *)ascii, "-X");
					xpos = fontHeight-1;
					ypos = (height/2) + fontWidth;
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, CYAN);
				} else if (pose == POSE_P_Y) {
					ESP_LOGI(TAG, "+Y");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 0);
					strcpy((char *)ascii, "+Y");
					xpos = (width/2) - fontWidth;
					ypos = fontHeight-1;
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, RED);
				} else if (pose == POSE_M_Y) {
					ESP_LOGI(TAG, "-Y");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 2);
					strcpy((char *)ascii, "-Y");
					xpos = (width/2) + fontWidth;
					ypos = height - fontHeight-1;
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, CYAN);
				} else if (pose == POSE_P_Z) {
					ESP_LOGI(TAG, "+Z");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 1);
					strcpy((char *)ascii, "+Z");
					xpos = (width/2) - (fontHeight/2);
					ypos = (height/2) - (fontWidth/2);
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, RED);
				} else if (pose == POSE_M_Z) {
					ESP_LOGI(TAG, "-Z");
					lcdFillScreen(&dev, BLACK);
					lcdSetFontDirection(&dev, 1);
					strcpy((char *)ascii, "-Z");
					xpos = (width/2) - (fontHeight/2);
					ypos = (height/2) - (fontWidth/2);
					lcdDrawString(&dev, fx32G, xpos, ypos, ascii, CYAN);
				} else {
					lcdFillScreen(&dev, BLACK);
				}
				prev_pose = pose;
			} // from imu
			if (motion6.sender == SENDER_BUTTON) {
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
