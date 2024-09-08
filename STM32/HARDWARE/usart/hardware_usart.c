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
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��	
	
	//����3��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	
  //USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11 ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
  
	//Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������3


 	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�	
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 	
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