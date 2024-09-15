#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"

int main(void)
{ 
	delay_init(168);
	LED_Init();
	KEY_Init();
	while(1)
	{
		uint8_t key = KEY_Scan(1);
		if(key==1){
			GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		}else if(key==2){
			GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		}
		// freertos_demo();
	}
}
