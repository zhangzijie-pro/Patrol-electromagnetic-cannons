#include "sys.h"
#include "delay.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"
#include "hc04.h"
#include "pwm.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t buffer[2];

int main(void)
{ 
	hc_init();
	PWM_initialize();
	LED_Init();
	delay_init(168);
	hc_prinf("hello,world\r\n");
	hc_sendString("test1:\r\n");
	PWM_set_compare(100-1);
	while(1)
	{
			if(hc_receive_ok_flag){
				hc_receive_ok_flag=0;
				for(int i=0;i<2;i++){
					buffer[i]=HC_Serial_Buffer[i];
				}
				hc_sendArray(buffer,2);

			}
		// freertos_demo();
	}
}
