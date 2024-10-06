
//*  you can config in your main */

 处理左侧雷达
void deal_left_radar(void){
		Get_data_len();
		if(radar_receive_ok_flag){
			radar_receive_ok_flag=0;
//			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
//			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
			
			deal_to_ld2412(radar_Serial_Buffer,&target_status,&motion_distance,&movingTargetZone,&static_distance,&stationaryTargetZone);
			uint8_t target = return_target_state(target_status);
			if(target!=0){
				left_exist=1;
			}else{
				left_exist=0;
			}
//			esp_prinf("运动目标距离:%d, 在第%d区间\r\n",motion_distance,movingTargetZone);
//			esp_prinf("静止目标距离:%d, 在第%d区间\r\n",static_distance,stationaryTargetZone);
		}
}

// 处理右侧雷达
void deal_right_radar(void){
		Get_right_data_len();
		if(right_radar_receive_ok_flag){
			right_radar_receive_ok_flag=0;
			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
			
			deal_to_ld2412(right_radar_Serial_Buffer,&right_target_status,&right_motion_distance,&right_movingTargetZone,&right_static_distance,&right_stationaryTargetZone);
			uint8_t target = return_target_state(right_target_status);
			if(target!=0){
				right_exist=1;
			}else{
				right_exist=0;
			}
//			esp_prinf("运动目标距离:%d, 在第%d区间\r\n",right_motion_distance,right_movingTargetZone);
//			esp_prinf("静止目标距离:%d, 在第%d区间\r\n",right_static_distance,right_stationaryTargetZone);
		}
}

uint8_t return_target_state(uint8_t target){
		switch(target){
			case 0:
				return 0;
				break;
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			case 3:
				return 3;
				break;
			default:
				return 0;
				break;
		}
}

// 得到目标角度 -> 旋转舵机  -> 开启esp32  ->  等待返回值
void Get_Angle_Servo(void){
	if((right_exist==1)&&(left_exist==1)){
		right_exist=0;
		left_exist=0;
		double target_angle = Get_Angle_from_radar();
		esp_prinf("%.2f",target_angle);
		Servo_Angle_down(target_angle);
		// 发送 开启 esp32 指令
		esp_send_content(Start_Esp32,2);
		// 处理esp32内容
		esp32_data();
		if(Get_esp_content) {
			deal_esp32_return_content(esp_content);
			Get_esp_content=0;
		}
	}
}