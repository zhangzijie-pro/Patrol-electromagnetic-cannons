#include "main.h"

void return_target_state(void);

int main(void)
{
	uint8_t i = 0;

	// ���贮�ڳ�ʼ��
	hc_init();
	esp_init();
	radar_usart_init();
	
	// �����ʼ��
	Servo_Init();
	
	// С����ʼ��
	Car_Init();
	
	// LED��ʼ��
	LED_Init();
	delay_init(168);
	
	esp_prinf("hello,esp\r\n");
	hc_prinf("hello,hc\r\n");
	Car_Set_Speed(1000);
	//start_engineer();.
	//esp_prinf("engineer model: %d\r\n",engineer_state);
	while(1)
	{
		Get_data_len();
		if(radar_receive_ok_flag){
			radar_receive_ok_flag=0;
			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
//			esp_prinf("�˶�Ŀ�����:%d\r\n",(radar_Serial_Buffer[6] << 8) | radar_Serial_Buffer[5]);
//			esp_prinf("��ֹĿ�����:%d\r\n",(radar_Serial_Buffer[8] << 8) | radar_Serial_Buffer[7]);
			
			deal_to_ld2412(radar_Serial_Buffer,&target_status,&motion_distance,&movingTargetZone,&static_distance,&stationaryTargetZone);
			esp_prinf("Ŀ��״̬:");
			return_target_state();
			esp_prinf("�˶�Ŀ�����:%d, �ڵ�%d����\r\n",motion_distance,movingTargetZone);
			esp_prinf("��ֹĿ�����:%d, �ڵ�%d����\r\n",static_distance,stationaryTargetZone);
			
		}
		
		// ����esp32�õ�����
//		if(esp_receive_ok_flag){
//			esp_receive_ok_flag=0;
//			i=0;
//			while(esp_counter--){
//				USART_SendData(USART3,esp_Serial_Buffer[i++]);
//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
//			}
//			esp_counter=0;
//		}
		
		// freertos_demo();
	}
}

void return_target_state(void){
		switch(target_status){
			case 0:
				esp_prinf("û�з���Ŀ��");
				break;
			case 1:
				esp_prinf("�����˶�Ŀ��");
				break;
			case 2:
				esp_prinf("���־�ֹĿ��");
				break;
			case 3:
				esp_prinf("�����˶��뾲ֹĿ��");
				break;
			default:
				esp_prinf("����û��Ŀ��");
				break;
		}
}


// ����������������
void USART2_IRQHandler(void){
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			hc_data = USART_ReceiveData(USART2);
			
			if(hc_data == '0'){			// receive 49-'0'
				LED1=0;
				Car_Forward();
				Servo_Angle_up(0);
				Servo_Angle_down(0);
			}
			else if(hc_data=='1'){
				LED1=1;
				Car_Back();
				Servo_Angle_up(45);
				Servo_Angle_down(45);
			}
			else if(hc_data=='2'){
				LED2=1;
				Car_Turn_Left();
				Servo_Angle_up(90);
				Servo_Angle_down(90);
			}
			else if(hc_data=='3'){
				LED2=0;
				Car_Turn_Right();
				Servo_Angle_up(135);
				Servo_Angle_down(135);
			}
			else if(hc_data=='4'){
				Car_Stop();
				Servo_Angle_up(180);
				Servo_Angle_down(180);
			}
		}
}