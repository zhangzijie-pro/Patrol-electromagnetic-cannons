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
#ifndef __usart_h__
#define __usart_h__

//----------------------- Include files ------------------------//

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 100

//------------------------- Data struct ------------------------//
static int send_string_to_usart4(char * str);
static int send_byte_to_usart4(char data);
static int initialize_usart4(unsigned long int baudrate);
static int printf(const char * fmt,...);
static int send_buffer4(void * ,int);

//----------------------- Extern variable ----------------------//
#endif // __uart_h__
