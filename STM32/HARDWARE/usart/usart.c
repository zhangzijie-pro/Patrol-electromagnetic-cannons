// ����
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
#include "usart.h"

//--------------------------- Variable --------------------------// 
//usart4 debug
static int send_string_to_usart4(char * str);
static int send_byte_to_usart4(char data);
static int initialize_usart4(unsigned long int baudrate);
static int printf(const char * fmt,...);
static int send_buffer4(void * ,int);

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
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);             // GPIOʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                        //PA0Ϊ�����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                        //PA1Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);           //PA0���Ÿ���ΪUART4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);           //PA1���Ÿ���ΪUART4
	
	USART_DeInit(UART4);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);            //UART4ʱ��ʹ��
	  
	USART_InitStructure.USART_BaudRate = baudrate;                   //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //8������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           //1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;             //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure);                         //��ʼ��UART4
	USART_Cmd(UART4, ENABLE);                                        //ʹ��UART4
	USART_ITConfig(UART4,USART_IT_PE,ENABLE);
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);                      //��UART4���ж�
	
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
static int 
send_buffer4(void * buf,int len)                                  
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
static int send_byte_to_usart4(char data)          	                          //TTLͨ��
{
	while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));          //�ȴ������������
	USART_SendData(UART4,data);                                       //������д�����ݼĴ�����
	
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
static int printf(const char * fmt,...)             		                    //����4���
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
