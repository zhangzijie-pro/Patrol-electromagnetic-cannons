#include "hc04.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "led.h"

uint8_t HC_Serial_Buffer[HC_BUFFER_MAX_LEN];
uint8_t hc_receive_ok_flag=0;
uint8_t hc_counter=0;
uint8_t hc_data;

void hc_init(void)
{
	  USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
    // 使能时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // 配置 GPIO 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		
		USART_DeInit(USART2);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
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
		//USART_ITConfig(USART2,USART_IT_PE,ENABLE);
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}


void hc_sendbyte(uint8_t Byte){
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 1));
	USART_SendData(USART2,Byte);  
}

void hc_sendArray(uint8_t *Array, uint16_t len)
{
	char *p = (char *)Array;
	
	while(len --){
		hc_sendbyte(*p);
		p ++;
	}
}

void hc_sendString(char *String)
{
	while(*String!='\0')
	{
		while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 1));
		USART_SendData(USART2,*String++);
	}
}

void hc_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	hc_sendString(String);
}