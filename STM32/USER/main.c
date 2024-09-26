#include "main.h"

int main(void)
{
	uint8_t i = 0;
	// ���贮�ڳ�ʼ��
	hc_init();
	esp_init();
	// �����ʼ��
	Servo_Init();
	// С����ʼ��
	//PWM_initialize();
	Car_Init();
	
	// LED��ʼ��
	LED_Init();
	delay_init(168);
	
	// LCD ��ʼ��
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	
	esp_prinf("hello,esp\r\n");
	hc_prinf("hello,hc");

	

	
	Servo_Angle(0);
	while(1)
	{
		// LCD��ʾ
		LCD_ShowChar(20,20,1,WHITE,BLACK,12,1);//��ʾһ���ַ�
		
		// ����esp32�õ�����
		if(esp_receive_ok_flag){
			esp_receive_ok_flag=0;
			i=0;
			while(esp_counter--){
				USART_SendData(USART3,esp_Serial_Buffer[i++]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
			}
			esp_counter=0;
		}
		
		// freertos_demo();
	}
}

// ����������������
void USART2_IRQHandler(void){
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			hc_data = USART_ReceiveData(USART2);
			
			if(hc_data == '1'){			// receive 49-'0'
				LED1=0;
				PWM_set_compare(400-1);
				Servo_Angle(90);
			}
			else if(hc_data=='0'){
				LED1=1;
				PWM_set_compare(500-1);
				Servo_Angle(45);
			}
			else if(hc_data=='2'){
				LED2=1;
				PWM_set_compare(600-1);
				Servo_Angle(135);
			}
				else if(hc_data=='3'){
				LED2=0;
				PWM_set_compare(800-1);
				Servo_Angle(180);
			}
		}
}