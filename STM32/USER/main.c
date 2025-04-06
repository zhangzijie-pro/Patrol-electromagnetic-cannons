#include "main.h"

/***************************************************************
     
													函数声明

****************************************************************/
void esp32_data();
void radar_data(void);
float judgment_data(Target_msg *msg);
/***************************************************************
     
													变量声明

****************************************************************/
// 开灯
uint8_t cmd1 = 0x01;
uint16_t cmd1_Array[2]={0x01,0x00};

// 开启摄像头: 前两位0001 开启摄像头, 后面0001为选择模式{1:识别人体,2,识别危险物体}
uint8_t cmd2 = 0x02;
uint16_t cmd2_Array[4]={0x01,0x00,0x01,0x00};

// 声明3个目标结构体
Target_msg target1;
Target_msg target2;
Target_msg target3;

// Servo  radar
float angle_radar_1;
float angle_radar_2;
float angle_radar_3;

float angle_radar;

// Car
uint8_t speed = (uint8_t)400;

uint8_t i = 0;		// 计数
// esp
uint8_t esp_content[6];
uint8_t Get_esp_content=0;		// esp是否接受到数据
/***************************************************************************************************
     
					GET_ANGLE -> Servo -> Send esp32 -> start_esp32 -> return content

***************************************************************************************************/


int main(void)
{
	// 外设串口初始化
	hc_init();
	esp_init();
	radar_usart_init();
	
	// 舵机初始化
	Servo_Init();
	Servo_Angle_down(90);
	Servo_Angle_up(90);
	
	// 小车初始化
	Car_Init();
	Car_Set_Speed(1000);
	// LED初始化
	LED_Init();
	delay_init(168);
	
	esp_prinf("hello,esp\r\n");
	hc_prinf("hello,hc\r\n");

	while(1)
	{
		LED1=0;
		LED2=0;
		radar_data();
		
//		// 处理esp32内容
//		esp32_data();
//		if(Get_esp_content) {
//			deal_esp32_return_content(esp_content);
//			Get_esp_content=0;
//		}
		
		// freertos_demo();
	}
}

// 得到esp32返回报文内容
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

void radar_data(void){
//	Get_data_len();
		if(radar_receive_ok_flag){
			radar_receive_ok_flag=0;
#if LD_MODE
			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
			
			deal_to_ld2412(radar_Serial_Buffer,&target_status,&motion_distance,&movingTargetZone,&static_distance,&stationaryTargetZone);
			esp_prinf("目标信息:");
			return_target_state();
			esp_prinf("\r\n运动目标距离:%d, 在第%d区间\r\n",motion_distance,movingTargetZone);
			esp_prinf("静止目标距离:%d, 在第%d区间\r\n",static_distance,stationaryTargetZone);
#else
			// 处理目标1
			deal_ld2450_data(target_one,&target1);
			angle_radar_1 = judgment_data(&target1);
			// get angle -> To Servo
			esp_prinf("target 1: %d",target1.Have_data);
			float len = sqrt((target1.X_pos*target1.X_pos)+(target1.Y_pos*target1.Y_pos))/10000;	//m
			esp_prinf("x: %d, y: %d, len: %.2f angle: %.2f\r\n",target1.X_pos,target1.Y_pos,len,target1.Angle);
			
			// 处理目标2
			deal_ld2450_data(target_two,&target2);
			angle_radar_2 = judgment_data(&target2);
			esp_prinf("target 2: %d",target2.Have_data);
			esp_prinf("x: %d, y: %d, angle: %.2f\r\n",target2.X_pos,target2.Y_pos,target2.Angle);
			
			// 处理目标3
			deal_ld2450_data(target_three,&target3);
			angle_radar_3 = judgment_data(&target3);
			esp_prinf("target 3: %d",target3.Have_data);
			esp_prinf("x: %d, y: %d, angle: %.2f\r\n",target3.X_pos,target3.Y_pos,target3.Angle);
			
			
			if(angle_radar_2==0.0&&angle_radar_3==0.0){
				// 只有一个目标
			}else if(angle_radar_2!=0.0&&angle_radar_3==0.0){
				float angle_sum = angle_radar_1+angle_radar_2;
				if(angle_sum<120){
					angle_radar = angle_sum/2;
				}
			}else if(angle_radar_2!=0.0&&angle_radar_3!=0.0){
				
			}
#endif
		}
}

float judgment_data(Target_msg *msg){
	if(msg->Have_data){
		return msg->Angle;
	}else{
		return 0.0;
	}
}



// 处理蓝牙发送内容
void USART2_IRQHandler(void){
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			hc_data = USART_ReceiveData(USART2);
			
			// 前进
			if(hc_data == '0'){			// receive 49-'0'
				LED1=0;
				Car_Forward();
				Servo_Angle_up(0);
				Servo_Angle_down(0);
			}
			// 后退
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
			}else if(hc_data=='5'){
				speed+=50;
				if(speed > (uint8_t)1000) speed=(uint8_t)1000;
				Car_Set_Speed(speed);
			}
		}
}