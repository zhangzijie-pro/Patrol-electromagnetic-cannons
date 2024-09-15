#include "hardware_usart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

static int send_byte_to_usart2(char data);
static int init_usart2(unsigned long int baudrate);
static int send_buffer2(void *buf, int len);
static int send_string_to_usart2(char *str);
static int printf2(const char * fmt,...);

UART_T usart2 = {
	.receive_ok_flag = 0,
	.counter=0,
	.send_byte = send_byte_to_usart2,
	.send_string = send_string_to_usart2,
	.init = init_usart2,
	.printf=printf2,
	.send_buffer = send_buffer2
};

static int init_usart2(unsigned long int baudrate) {
	
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
	
    // 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // 配置 GPIO 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  // PA2 -> TX, PA3 -> RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		
		USART_DeInit(USART2);
    // 配置 USART 参数
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

		
    // 使能 USART
    USART_Cmd(USART2, ENABLE);
		USART_ITConfig(USART2,USART_IT_PE,ENABLE);
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		return 0;
}

static int send_buffer2(void *buf, int len){
		char *p = (char*)buf;
		if(len<=0)return -1;
	
		while(len--){
			send_byte_to_usart2(*p);
			p++;
		}
		return 0;
}

static int send_byte_to_usart2(char data){
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)==1));
	USART_SendData(USART2,data);
	
	return 0;
}

static int send_string_to_usart2(char *str){
	while(*str!='\0'){
		while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)==1));
		USART_SendData(USART2,*str++);
	}
	
	return 0;
}

int usart2_IRQHandler(void)
{	
  while(USART_GetFlagStatus(UART4,USART_FLAG_RXNE) == 0);                                                                 
 	usart2.receive_buffer[usart2.counter++]=USART_ReceiveData(UART4); //????????
 	
 	if(usart2.receive_buffer[usart2.counter - 1] == '\n' && usart2.receive_buffer[usart2.counter - 2] == '\r'){   			
			usart2.receive_buffer[usart2.counter-1]=0;
 			usart2.counter=0;                                
 	   	usart2.receive_ok_flag=1;                      
		}
	return 0;			
}

static int printf2(const char * fmt,...)             		                    //????4???
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
