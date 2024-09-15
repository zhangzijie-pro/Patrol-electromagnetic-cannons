#ifndef __HC_H
#define __HC_H	 

#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>

void hc_init(void);
void hc_sendbyte(uint8_t Byte);
void hc_sendArray(uint8_t *Array, uint16_t len);
void hc_sendString(char *String);
uint32_t hc_pow(uint32_t x,uint32_t y);
void hc_sendNumber(uint32_t Number, uint8_t len);
int hc_fputc1(int ch, FILE *f);
void hc_prinf(char *format,...);
uint8_t hc_GetRxFlag(void);
uint8_t hc_GetRxData(void);
#endif
