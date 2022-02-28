#ifndef _HTTP_SERVER_APP_H_
#define _HTTP_SERVER_APP_H_
#include <stdint.h>

typedef void (*http_post_callback_t) (uint8_t * data, uint16_t len); 
typedef void (*http_get_callback_t) (void); 


void start_webserver(void);
void stop_webserver(void);
void http_set_callback_switch(void * cb);
void http_set_callback_dht11(void * cb); 
void http_set_callback_slider(void * cb); 
void dht11_response(char * data, int len); 
#endif 