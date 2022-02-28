#ifndef ESP32_UART_H
#define ESP32_UART_H
#include <hal/uart_types.h>
#include <esp_err.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <freertos/queue.h>
#include "freertos/message_buffer.h"

#pragma pack(1)
typedef struct
{
    uart_port_t port_num; 
    size_t uart_length; 
    char * message; 
} intr_message_t;
#pragma pack() 

typedef void (*uart_callback_t)(intr_message_t message);        

void esp32_uart_config(uart_port_t uart_num, int baud, int buffer_size); 
void esp32_uart_log(uart_port_t uart_num, const char * str,...);
void esp32_uart_set_rx_callback(void * callback); 
void esp32_uart_read_string(uart_port_t uart_num); 
uint32_t esp32_uart_available(); 
void esp32_clear_buffer(); 
#endif