#include "esp32.h"
#include "stm32f4xx.h"

uint8_t esp_Serial_RxData;
uint8_t esp_Serial_RxFlag=0;

void esp_init(void)
{
	      // 1. ʹ��USART3��GPIOAʱ��
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // 2. ����PB10 (TX) �� PB11 (RX) Ϊ���ù���
    GPIOB->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
    GPIOB->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1); // ����ģʽ
    GPIOB->AFR[1] |= 0x0077; // ����PB10��PB11ΪAF7��USART3��

    // 3. ����USART3
    USART3->BRR = (uint16_t)(SystemCoreClock / 115200); // ������115200
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE; // ʹ�ܷ��ͺͽ���
    USART3->CR1 |= USART_CR1_RXNEIE; // ʹ�ܽ����ж�
    USART3->CR1 |= USART_CR1_UE; // ʹ��USART3

    // 4. ʹ��USART3�ж�
    NVIC_EnableIRQ(USART3_IRQn);
}

void esp_IRQHandler(void){
	if(USART3->SR & USART_SR_RXNE){
		esp_Serial_RxData = USART3->DR;
		esp_Serial_RxFlag = 1;
	}
}

void esp_sendbyte(uint8_t Byte){
	while(!(USART3->SR&USART_SR_TXE));
	USART3->DR = Byte;
}

void esp_sendArray(uint8_t *Array, uint16_t len)
{
	for(uint16_t i=0;i<len;i++){
		esp_sendbyte(Array[i]);
	}
}

void esp_sendString(char *String)
{
	while(*String)
	{
		esp_sendbyte(*String++);
	}
}

uint32_t esp_pow(uint32_t x,uint32_t y)
{
	uint32_t result = 1;
	for(uint32_t i=0;i<y;i++){
		result*=x;
	}
	return result;
}

void esp_sendNumber(uint32_t Number, uint8_t len)
{
	for(int i=len;i>0;i--){
		uint8_t digit = (Number/esp_pow(10,i-1))%10;
		esp_sendbyte(digit+'0');
	}
}

int esp_fputc1(int ch, FILE *f)
{
	esp_sendbyte(ch);
	return ch;
}

void esp_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	esp_sendString(String);
}

uint8_t esp_GetRxFlag(void)
{
	return esp_Serial_RxFlag;
}

uint8_t esp_GetRxData(void)
{
	esp_Serial_RxFlag = 0;
	return esp_Serial_RxData;
}
