#ifndef __esp_h__
#define __esp_h__

#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>

#define ESP_BUFFER_MAX_LEN 100  // 假设数组长度为100

extern uint8_t esp_Serial_Buffer[ESP_BUFFER_MAX_LEN];
extern uint8_t esp_receive_ok_flag;
extern uint8_t esp_counter;

void esp_init(void);
void esp_sendbyte(uint8_t Byte);
void esp_sendArray(uint8_t *Array, uint16_t len);
void esp_sendString(char *String);
void esp_prinf(char *format,...);

#endif
