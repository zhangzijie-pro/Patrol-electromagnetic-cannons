#include "sys.h"
#include "delay.h"
#include "freertos_demo.h"
#include "led.h"
#include "key.h"
#include "pwm.h"
#include "hc04.h"
#include "stm32f4xx.h"
#include "Servo.h"
#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t buffer[4];

int main(void)
{
	hc_init();
	Servo_Init();
	PWM_initialize();
	LED_Init();
	delay_init(168);
	hc_prinf("hello,hc");
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	PWM_set_compare(100-1);
	//Servo_Angle(90);
	while(1)
	{
		LCD_ShowChar(20,20,1,BLACK,BLACK,12,1);//显示一个字符
		// freertos_demo();
		Servo_Angle(0);    // 设置舵机转到0度
		delay_ms(1000);
	}
}

// 处理蓝牙发送内容
void USART2_IRQHandler(void){
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			hc_data = USART_ReceiveData(USART2);
			
			if(hc_data == '1'){			// receive 49-'0'
				LED1=0;
				PWM_set_compare(25-1);
				Servo_Angle(90);
			}
			else if(hc_data=='0'){
				LED1=1;
				PWM_set_compare(50-1);
				Servo_Angle(180);
			}
//			HC_Serial_Buffer[hc_counter++] = USART_Receive_data(USART2);
//			
//			if(HC_Serial_Buffer[hc_counter-1]=='\n' && HC_Serial_Buffer[hc_counter-2] == '\r')
//			{
//				HC_Serial_Buffer[hc_counter-1]=0;
//				hc_counter=0;
//				hc_receive_ok_flag=1;
//			}
		}
}