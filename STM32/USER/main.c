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
	Car_Init();
	
	// LED��ʼ��
	LED_Init();
	delay_init(168);
	
	esp_prinf("hello,esp\r\n");
	hc_prinf("hello,hc\r\n");

	while(1)
	{
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
				Servo_Angle_up(90);
				Servo_Angle_down(90);
			}
			else if(hc_data=='0'){
				LED1=1;
				Servo_Angle_up(45);
				Servo_Angle_down(45);
			}
			else if(hc_data=='2'){
				LED2=1;
				Servo_Angle_up(135);
				Servo_Angle_down(135);
			}
			else if(hc_data=='3'){
				LED2=0;
				Servo_Angle_up(180);
				Servo_Angle_down(180);
			}
			else if(hc_data=='4'){
				Servo_Angle_up(0);
				Servo_Angle_down(0);
			}
		}
}