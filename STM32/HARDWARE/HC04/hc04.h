#ifndef __HC04_H
#define __HC04_H	 

#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>

#define HC_BUFFER_MAX_LEN 100

void hc_init(void);
void hc_sendbyte(uint8_t Byte);
void hc_sendArray(uint8_t *Array, uint16_t len);
void hc_sendString(char *String);
void hc_prinf(char *format,...);

extern uint8_t HC_Serial_Buffer[HC_BUFFER_MAX_LEN];
extern uint8_t hc_receive_ok_flag;
extern uint8_t hc_counter;

#endif
