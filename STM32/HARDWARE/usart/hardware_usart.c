// ????
//------------------------ Include files ------------------------//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#include "..\fwlib\inc\stm32f4xx_rcc.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"
#include "..\fwlib\inc\stm32f4xx_usart.h"
#include "hardware_usart.h"

//--------------------------- Variable --------------------------// 
//usart4 debug
static int send_string_to_usart4(char * str);
static int send_byte_to_usart4(char data);
static int initialize_usart4(unsigned long int baudrate);
static int my_printf4(const char * fmt,...);
static int send_buffer4(void * ,int);

//usart2 debug
static int send_string_to_usart2(char * str);
static int send_byte_to_usart2(char data);
static int initialize_usart2(unsigned long int baudrate);
static int my_printf2(const char * fmt,...);
static int send_buffer2(void * ,int);

UART_T usart4 = {
	.receive_ok_flag=0,
	.counter=0,
	.send_byte = send_byte_to_usart4,
	.send_string = send_string_to_usart4,
	.initialize=initialize_usart4,
	.printf=my_printf4,
	.send_buffer = send_buffer4
	};

	UART_T usart2 = {
	.receive_ok_flag=0,
	.counter=0,
	.send_byte = send_byte_to_usart2,
	.send_string = send_string_to_usart2,
	.initialize=initialize_usart2,
	.printf=my_printf2,
	.send_buffer = send_buffer2
	};
	
//--------------------------- Function --------------------------//
//USART4 DEBUG
/*
 * Name               : initialize_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int initialize_usart4(unsigned long int baudrate)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);             // GPIO??????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                        //PA0????????????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                        //PA1?????????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);           //PA0????????UART4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);           //PA1????????UART4
	
	USART_DeInit(UART4);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);            //UART4??????
	  
	USART_InitStructure.USART_BaudRate = baudrate;                   //??????
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //8??????¦Ë
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           //1????¦Ë
	USART_InitStructure.USART_Parity = USART_Parity_No ;             //?????§µ??¦Ë
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //?????
	USART_Init(UART4, &USART_InitStructure);                         //?????UART4
	USART_Cmd(UART4, ENABLE);                                        //???UART4
	USART_ITConfig(UART4,USART_IT_PE,ENABLE);
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);                      //??UART4???§Ø?
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	return 0;
}

/*
 * Name               : send_buffer4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_buffer4(void * buf,int len)                                  
{
	char *p = (char *)buf;
	
	if(len <= 0)return -1;
	
	while(len --){
		send_byte_to_usart4(*p);
		p ++;
	}
	
	return 0;
}

/*
 * Name               : send_byte_to_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_byte_to_usart4(char data)          	                          //TTL???
{
	while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));          //??????????????
	USART_SendData(UART4,data);                                       //??????§Õ????????????
	
	return 0;
}

/*
 * Name               : send_string_to_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_string_to_usart4(char * str)
{
	while(*str!='\0'){
		while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));
		USART_SendData(UART4,*str++);	
	}
	return 0;
}

/*
 * Name               : UART4_IRQHandler
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
int UART4_IRQHandler(void)
{	
  while(USART_GetFlagStatus(UART4,USART_FLAG_RXNE) == 0);                                                                 
 	usart4.receive_buffer[usart4.counter++]=USART_ReceiveData(UART4); //????????
 	
 	if(usart4.receive_buffer[usart4.counter - 1] == '\n' && usart4.receive_buffer[usart4.counter - 2] == '\r'){   			
			usart4.receive_buffer[usart4.counter-1]=0;
 			usart4.counter=0;                                
 	   	usart4.receive_ok_flag=1;                      
 		}
	return 0;			
}

/*
 * Name               : printf
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int my_printf4(const char * fmt,...)             		                    //????4???
{
	__va_list arg_ptr; 
	char buf[UART_BUFFER_SIZE];
  		
	memset(buf,'\0',sizeof(buf));

	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart4(buf);

	return 0;
}

//--------------------------- Function --------------------------//
//USART4 DEBUG
/*
 * Name               : initialize_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int initialize_usart2(unsigned long int baudrate)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);             // GPIO??????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                        //PA0????????????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                        //PD6?????????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);           //PA0????????USART2
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);           //PA1????????USART2
	
	USART_DeInit(USART2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);            //USART2??????
	  
	USART_InitStructure.USART_BaudRate = baudrate;                   //??????
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //8??????¦Ë
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           //1????¦Ë
	USART_InitStructure.USART_Parity = USART_Parity_No ;             //?????§µ??¦Ë
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //?????
	USART_Init(USART2, &USART_InitStructure);                         //?????USART2
	USART_Cmd(USART2, ENABLE);                                        //???USART2
	USART_ITConfig(USART2,USART_IT_PE,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                      //??USART2???§Ø?
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	return 0;
}

/*
 * Name               : send_buffer4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_buffer2(void * buf,int len)                                  
{
	char *p = (char *)buf;
	
	if(len <= 0)return -1;
	
	while(len --){
		send_byte_to_usart2(*p);
		p ++;
	}
	
	return 0;
}

/*
 * Name               : send_byte_to_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_byte_to_usart2(char data)          	                          //TTL???
{
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 1));          //??????????????
	USART_SendData(USART2,data);                                       //??????§Õ????????????
	
	return 0;
}

/*
 * Name               : send_string_to_usart4
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int send_string_to_usart2(char * str)
{
	while(*str!='\0'){
		while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 1));
		USART_SendData(USART2,*str++);	
	}
	return 0;
}

/*
 * Name               : UART4_IRQHandler
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
int USART2_IRQHandler(void)
{	
  while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == 0);                                                                 
 	usart2.receive_buffer[usart2.counter++]=USART_ReceiveData(USART2); //????????
 	
 	if(usart2.receive_buffer[usart2.counter - 1] == '\n' && usart2.receive_buffer[usart2.counter - 2] == '\r'){   			
			usart2.receive_buffer[usart2.counter-1]=0;
 			usart2.counter=0;                                
 	   	usart2.receive_ok_flag=1;                      
 		}
	return 0;			
}

/*
 * Name               : printf
 * Description        : ---
 * Author             : XiaomaGee
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 11/21/2015
 *
 * create.
 * -------------------
 */
static int my_printf2(const char * fmt,...)             		                    //????2???
{
	__va_list arg_ptr; 
	char buf[UART_BUFFER_SIZE];
  		
	memset(buf,'\0',sizeof(buf));

	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart2(buf);

	return 0;
}

