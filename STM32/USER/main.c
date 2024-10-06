#include "main.h"

/***************************************************************
     
													��������

****************************************************************/
void esp32_data();

/***************************************************************
     
													��������

****************************************************************/
// ����
uint8_t cmd1 = 0x01;
uint16_t cmd1_Array[2]={0x01,0x00};
// ��������ͷ: ǰ��λ0001 ��������ͷ, ����0001Ϊѡ��ģʽ{1:ʶ������,2,ʶ��Σ������}
uint8_t cmd2 = 0x02;
uint16_t cmd2_Array[4]={0x01,0x00,0x01,0x00};

// ����3��Ŀ��ṹ��
Target_msg target1;
Target_msg target2;
Target_msg target3;

uint8_t i = 0;		// ����
uint8_t esp_content[6];
uint8_t Get_esp_content=0;		// esp�Ƿ���ܵ�����
/***************************************************************************************************
     
					GET_ANGLE -> Servo -> Send esp32 -> start_esp32 -> return content

***************************************************************************************************/


int main(void)
{
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
	while(1)
	{
//	Get_data_len();
		if(radar_receive_ok_flag){
			radar_receive_ok_flag=0;
#if LD_MODE
			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
			
			deal_to_ld2412(radar_Serial_Buffer,&target_status,&motion_distance,&movingTargetZone,&static_distance,&stationaryTargetZone);
			esp_prinf("Ŀ����Ϣ:");
			return_target_state();
			esp_prinf("\r\n�˶�Ŀ�����:%d, �ڵ�%d����\r\n",motion_distance,movingTargetZone);
			esp_prinf("��ֹĿ�����:%d, �ڵ�%d����\r\n",static_distance,stationaryTargetZone);
#else
			esp_prinf("%x\r\n",target_one[0]);
			esp_prinf("%x\r\n",target_one[1]);
			deal_ld2450_data(target_one,&target1);
			// get angle -> To Servo
			esp_prinf("x: %d, y: %d, angle: %.2f\r\n",target1.X_pos,target1.Y_pos,target1.Angle);
		
#endif
		}
		
		// ����esp32����
		esp32_data();
		if(Get_esp_content) {
			deal_esp32_return_content(esp_content);
			Get_esp_content=0;
		}
		
		// freertos_demo();
	}
}

// �õ�esp32��������
void esp32_data(){
		if(esp_receive_ok_flag){
			esp_receive_ok_flag=0;
			i=0;
			if(esp_Serial_Buffer[0]==0xAA){
				for(i=1;i<esp_counter;i++){
					esp_content[i-1]=esp_Serial_Buffer[i];
					if(esp_content[i-1]==0xFF){
						esp_content[i-1]=9;
						Get_esp_content=1;
					}
				}
			}
//			while(esp_counter--){
//				USART_SendData(USART3,esp_Serial_Buffer[i++]);
//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
//			}
			esp_counter=0;
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