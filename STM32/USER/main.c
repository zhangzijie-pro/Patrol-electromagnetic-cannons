#include "sys.h"
#include "delay.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"
#include "motor.h"

uint8_t RxData;

int main(void)
{ 
	Car_Init();
	LED_Init();
	delay_init(168);
	while(1)
	{
		// freertos_demo();
	}
}
