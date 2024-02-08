#include <sdkconfig.h>
#include <driver/ledc.h>

#include "Light_PWM.h"

#define PWM_BITS 9

void Light_PWM_init(uint32_t duty) {

	uint32_t _cfg_freq = 256;
	int16_t _cfg_pin_bl = 27;
	//uint8_t _cfg_offset = 40;
	uint8_t _cfg_pwm_channel = 7;
	bool _cfg_invert = 0;
	static ledc_channel_config_t ledc_channel;
	ledc_channel.gpio_num = (gpio_num_t)_cfg_pin_bl;
	ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;
	ledc_channel.channel = (ledc_channel_t)_cfg_pwm_channel;
	ledc_channel.intr_type = LEDC_INTR_DISABLE;
	ledc_channel.timer_sel = (ledc_timer_t)((_cfg_pwm_channel >> 1) & 3);
	ledc_channel.duty = _cfg_invert ? (1 << PWM_BITS) : 0;
	ledc_channel.hpoint = 0;
	ledc_channel_config(&ledc_channel);

	static ledc_timer_config_t ledc_timer;
	ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;
	ledc_timer.duty_resolution = (ledc_timer_bit_t)PWM_BITS; // resolution of PWM duty
	ledc_timer.freq_hz = _cfg_freq; // frequency of PWM signal
	ledc_timer.timer_num = ledc_channel.timer_sel; // timer index
	ledc_timer_config(&ledc_timer);

	//uint32_t duty = 295;
	ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)_cfg_pwm_channel, duty);
	ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)_cfg_pwm_channel);

	return;
}
