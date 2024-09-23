/*
 * FILE               : usart.h
 * DESCRIPTION        : This file is iCore3 usart file header.
 * Author             : XiaomaGee@Gmail.com
 * Copyright          :
 *
 * History
 * --------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * --------------------
 */
#ifndef __other_h__
#define __other_h__

//----------------------- Include files ------------------------//

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 100

//------------------------- Data struct ------------------------//
typedef struct{

	char receive_buffer[UART_BUFFER_SIZE];
	int counter;
 
	int receive_ok_flag;
	int baudrate;
	int error;
	int (* initialize)(unsigned long int);
	int (* send_string)(char *);
	int (* send_byte)(char);
	int (* send_buffer)(void *,int len);
	int (* printf)(const char * ,...);
}UART_T;

//----------------------- Extern function ----------------------//
extern UART_T usart4;

//----------------------- Extern variable ----------------------//
#endif // __uart_h__
