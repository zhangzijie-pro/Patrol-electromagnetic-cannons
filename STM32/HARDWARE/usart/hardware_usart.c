#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "hardware_usart.h"

void usart3_init();
int send_byte_to_usart3(char data);
int send_buffer3(void * buf,int len);
int send_string_to_usart4(char * str);
int send_byte_to_usart3(char data);
int printf4(const char * fmt,...); 

void usart3_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟	
	
	//串口3对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	
  //USART3端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11 ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
  
	//Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口3


 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断	
	USART_Cmd(USART3, ENABLE);                    //使能串口3 	
}

void USART3_IRQHandler(void)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) == 0)                                                           
 	receive_buffer[counter++]=USART_ReceiveData(UART4);
 	
 	if(receive_buffer[counter - 1] == '\n' && receive_buffer[counter - 2] == '\r'){   			
			receive_buffer[counter-1]=0;
 			counter=0;                                
 	   	receive_ok_flag=1;                      
 		}	
}

int send_buffer3(void * buf,int len)                                  
{
	char *p = (char *)buf;
	
	if(len <= 0)return -1;
	
	while(len --){
		send_byte_to_usart3(*p);
		p ++;
	}
	
	return 0;
}

int send_byte_to_usart3(char data)
{
	while(!(USART_GetFlagStatus(USART3,USART_FLAG_TC) == 1));
	USART_SendData(USART3,data);                                       
	
	return 0;
}

int send_string_to_usart4(char * str)
{
	while(*str!='\0'){
		while(!(USART_GetFlagStatus(USART3,USART_FLAG_TC) == 1));
		USART_SendData(USART3,*str++);	
	}
	return 0;
}

int printf4(const char * fmt,...)             		                    //????4???
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