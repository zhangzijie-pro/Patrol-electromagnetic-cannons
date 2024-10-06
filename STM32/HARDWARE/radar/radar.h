#ifndef __RADAR_H
#define __RADAR_H	

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define LD_MODE  0  			// 0: LD2450  1:LD2412

#if LD_MODE 
	extern uint8_t radar_Serial_Buffer[50];

#else
	extern uint8_t target_one[8];
	extern uint8_t target_two[8];
	extern uint8_t target_three[8];

#endif

extern uint8_t config_return[50];
extern uint8_t radar_receive_ok_flag;
extern uint8_t radar_counter;

void Get_data_len();
void radar_usart_init(void);
void radar_sendbyte(uint8_t Byte);
void radar_sendArray(const uint8_t *Array, uint16_t len);
void radar_sendString(char *String);
void radar_prinf(char *format,...);
#endif
