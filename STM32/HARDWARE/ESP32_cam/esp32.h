#ifndef __esp_h__
#define __esp_h__

#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>

void esp_init(void);
void esp_sendbyte(uint8_t Byte);
void esp_sendArray(uint8_t *Array, uint16_t len);
void esp_sendString(char *String);
uint32_t esp_pow(uint32_t x,uint32_t y);
void esp_sendNumber(uint32_t Number, uint8_t len);
int esp_fputc1(int ch, FILE *f);
void esp_prinf(char *format,...);
uint8_t esp_GetRxFlag(void);
uint8_t esp_GetRxData(void);

#endif
