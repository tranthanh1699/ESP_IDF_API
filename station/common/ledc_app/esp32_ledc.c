#include "esp32_ledc.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

static long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void esp32_ledc_init(void)
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_1,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    ledc_timer_config(&ledc_timer);
}

void esp32_ledc_add_gpio(gpio_num_t gpio_num, ledc_channel_t channel)
{
    ledc_channel_config_t ledc_channel = 
    {
        .channel    = channel,
        .duty       = 0,
        .gpio_num   = gpio_num,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0, 
        .timer_sel  = LEDC_TIMER_1
    };
    ledc_channel_config(&ledc_channel);
}

void esp32_ledc_set_dutycycle(ledc_channel_t channel, uint16_t duty)
{
    int duty_value = map(duty, 0, 100, 0, 8191); 
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty_value); 
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel); 
}
