#ifndef ESP32_LEDC_H
#define ESP32_LEDC_H
#include <hal/ledc_hal.h>
#include <hal/ledc_types.h>
#include <hal/gpio_types.h>

void esp32_ledc_init(void); 
void esp32_ledc_add_gpio(gpio_num_t gpio_num, ledc_channel_t channel); 
void esp32_ledc_set_dutycycle(ledc_channel_t channel, uint16_t duty); 
#endif