#include "hc04.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"

uint8_t HC_Serial_RxData;
uint8_t HC_Serial_RxFlag=0;

void hc_init(void)
{
	  USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
    // 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // 配置 GPIO 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  // PA2 -> TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //PA3 -> RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
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
}

void hc_IRQHandler(void){
	if(USART2->SR & USART_SR_RXNE){
		HC_Serial_RxData = USART2->DR;
		HC_Serial_RxFlag = 1;
	}
}

void hc_sendbyte(uint8_t Byte){
	while(!(USART2->SR&USART_SR_TXE));
	USART2->DR = Byte;
}

void hc_sendArray(uint8_t *Array, uint16_t len)
{
	for(uint16_t i=0;i<len;i++){
		hc_sendbyte(Array[i]);
	}
}

void hc_sendString(char *String)
{
	while(*String)
	{
		hc_sendbyte(*String++);
	}
}

uint32_t hc_pow(uint32_t x,uint32_t y)
{
	uint32_t result = 1;
	for(uint32_t i=0;i<y;i++){
		result*=x;
	}
	return result;
}

void hc_sendNumber(uint32_t Number, uint8_t len)
{
	for(int i=len;i>0;i--){
		uint8_t digit = (Number/hc_pow(10,i-1))%10;
		hc_sendbyte(digit+'0');
	}
}

int hc_fputc1(int ch, FILE *f)
{
	hc_sendbyte(ch);
	return ch;
}

void hc_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	hc_sendString(String);
}

uint8_t hc_GetRxFlag(void)
{
	return HC_Serial_RxFlag;
}

uint8_t hc_GetRxData(void)
{
	HC_Serial_RxFlag = 0;
	return HC_Serial_RxData;
}
