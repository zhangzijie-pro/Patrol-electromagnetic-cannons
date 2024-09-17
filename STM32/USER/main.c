#include "sys.h"
#include "delay.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"

uint8_t RxData;

int main(void)
{ 
	LED_Init();
	delay_init(168);
	while(1)
	{
		// receive
		if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE)==SET)
		{
			RxData=USART_ReceiveData(USART3);
		}
		// freertos_demo();
	}
}
