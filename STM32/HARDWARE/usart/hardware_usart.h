#ifndef __husart_h__
#define __husart_h__

//----------------------- Include files ------------------------//
#include "stm32f4xx.h"

#define UART_BUFFER_SIZE 100


//----------------------- Extern function ----------------------//
typedef struct{
	char receive_buffer[UART_BUFFER_SIZE];
	int counter;
	
	int receive_ok_flag;
	int baudrate;
	int error;
	int (* init)(unsigned long int);
	int (* send_string)(char *);
	int (* send_byte)(char);
	int (* send_buffer)(void *, int len);
	int (*printf)(const char*,...);
}UART_T;

extern UART_T usart2;

//----------------------- Extern variable ----------------------//
#endif // __uart_h__
