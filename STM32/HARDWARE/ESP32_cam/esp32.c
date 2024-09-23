#include "esp32.h"
#include "stm32f4xx.h"

uint8_t esp_Serial_Buffer[ESP_BUFFER_MAX_LEN];
uint8_t esp_receive_ok_flag=0;
uint8_t esp_counter=0;
uint8_t esp_data;

void esp_init(void)
{
		// 2. 配置PB10 (TX) 和 PB11 (RX) 为复用功能
		USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		// 配置 GPIO 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  // PB10 -> TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  //PB11 -> RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
	
		USART_DeInit(USART3);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		// 配置 USART3 参数
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);

		// 使能 USART
    USART_Cmd(USART3, ENABLE);
		USART_ITConfig(USART3,USART_IT_PE,ENABLE);
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
		
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void USART3_IRQHandler(void){
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
			esp_data = USART_ReceiveData(USART3);
		
			esp_prinf("receive :%d\r\n",esp_data-'0');
		}
}

void esp_sendbyte(uint8_t Byte){
	while(!(USART_GetFlagStatus(USART3,USART_FLAG_TC) == 1));
	USART_SendData(USART3,Byte);
}

void esp_sendArray(uint8_t *Array, uint16_t len)
{
		char *p = (char *)Array;
		
		while(len --){
			esp_sendbyte(*p);
			p ++;
		}
}

void esp_sendString(char *String)
{
	 while(*String!='\0')
	{
		while(!(USART_GetFlagStatus(USART3,USART_FLAG_TC) == 1));
		USART_SendData(USART3,*String++);
	}
}

void esp_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	esp_sendString(String);
}