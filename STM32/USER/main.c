#include "sys.h"
#include "delay.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"

int main(void)
{ 
	LED_Init();
	delay_init(168);
	while(1)
	{
		// freertos_demo();
	}
}
