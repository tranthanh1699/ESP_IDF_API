set(app_src esp32_uart.c)
set(pri_req ring_buffer)
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pri_req})
