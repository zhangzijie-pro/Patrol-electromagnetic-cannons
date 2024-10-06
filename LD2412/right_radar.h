#ifndef __RIGHT_RADAR_H
#define __RIGHT_RADAR_H	

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


extern uint8_t right_radar_Serial_Buffer[50];
extern uint8_t right_radar_receive_ok_flag;
extern uint8_t right_radar_counter;

void Get_right_data_len();
void right_radar_init(void);
void right_radar_sendbyte(uint8_t Byte);
void right_radar_sendArray(const uint8_t *Array, uint16_t len);
void right_radar_sendString(char *String);
void right_radar_prinf(char *format,...);

#endif
