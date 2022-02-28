/* LEDC (LED Controller) fade example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include <stdint.h>


void app_main(void)
{
    int ch;

    /*
     * Prepare and set configuration of timers
     * that will be used by LED Controller
     */
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_1,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);
 
    ledc_channel_config_t ledc_channel = 
    {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = GPIO_NUM_2,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0, 
        .timer_sel  = LEDC_TIMER_1
    };
    

    // Set LED Controller with previously prepared configuration
    ledc_channel_config(&ledc_channel);

    while (1) {
        for(uint16_t i = 0; i < 8192; i += 82)
        {
            ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, i); 
            ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel); 
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
}
