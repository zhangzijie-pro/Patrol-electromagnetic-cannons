#ifndef __RADAR_H
#define __RADAR_H	

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>



//RADAR_BUFFER_MAX_LEN
extern uint8_t radar_Serial_Buffer[50];
extern uint8_t radar_receive_ok_flag;
extern uint8_t radar_counter;

void Get_data_len();
void radar_usart_init(void);
void radar_sendbyte(uint8_t Byte);
void radar_sendArray(const uint8_t *Array, uint16_t len);
void radar_sendString(char *String);
void radar_prinf(char *format,...);
#endif
