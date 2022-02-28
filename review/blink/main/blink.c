/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/queue.h"
#include "string.h"

#define BIT_1 (1 << 1)

TaskHandle_t Task01Handle; 
TaskHandle_t Task02Handle; 
QueueHandle_t myQueueHandle; 

char txBuffer[100] = "Hello Task 2\n";
char rxBuffer[100]; 


void Task01(void * arg); 
void Task02(void * arg); 

void app_main(void)
{
    xTaskCreate(Task01, "task 01", 10000, NULL, 7, &Task01Handle); 
    xTaskCreate(Task02, "task 02", 10000, NULL, 6, &Task02Handle);
    myQueueHandle = xQueueCreate(10, sizeof(uint32_t)); 
    while(1)
    {
         vTaskDelay(9000 / portTICK_PERIOD_MS); 
    }
}

void Task01(void * arg)
{
    uint32_t count = 0; 
    while(1)
    {
        //sprintf(txBuffer, "Data Transmits: %d\n", count++); 
        printf("Data send: %d\n", count++);
        xQueueSend(myQueueHandle, &count, 2000); 
        vTaskDelay(2000 / portTICK_PERIOD_MS); 
    }
}
void Task02(void * arg)
{
    while(1)
    {   uint32_t data_receiver; 
        xQueueReceive(myQueueHandle, &data_receiver, portMAX_DELAY); 
        printf("Data Receiver: %d\n", data_receiver); 
    }
}
