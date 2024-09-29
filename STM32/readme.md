## Project

####  1.雷达模块： 检测是否前方目标有无静止或者运动的人体     LD2412      串口Usart
####  2.电磁炮部分....
####  3.串口连接esp32-cam进行目标检测锁定后返回人体的相对坐标,位置      
####  4.小车的移动        PWM,Motor     TIM4:(CH1-CH4) ---- PB6-PB9
####  5.蓝牙模块： 通过手机App实现对于设备的控制      HC-04    Usart


| 模块进度               |         剩余              |
|-----------------------|--------------------------|
| 小车部分| 完成|
| 舵机| 完成|
| 蓝牙| 完成|
| esp32| 未完成|
| 雷达| 未完成|
| 电磁炮| 未完成|

状态机
```c
switch(state){
				case STATE_IDLE:
					if(radar_data==RECEIVE_HEADER_1){
						state = STATE_HEADER;
						radar_counter=0;
					}
					break;
				case STATE_HEADER:
					if(radar_counter==0&&radar_data == RECEIVE_HEADER_2){
						radar_counter++;
					}else if(radar_counter==1&&radar_data == RECEIVE_HEADER_3){
						radar_counter++;
					}else if(radar_counter==2&&radar_data == RECEIVE_HEADER_4){
						radar_prinf("receive counter: %d, data: %x go to len\r\n",radar_counter,radar_data);
						radar_counter=0;
						state = STATE_LEN;
					}
					break;
					
				case STATE_LEN:
					radar_lendata[radar_counter++] = radar_data;
					if(radar_counter==1){
						radar_data_len = radar_lendata[1]<<8|radar_lendata[0];
						radar_prinf("data_len : %d\r\n",radar_data_len);
						radar_counter=0;
						radar_prinf("goto data\r\n");
						state = STATE_DATA;
					}
					break;
					
				case STATE_DATA:
					radar_Serial_Buffer[radar_counter++] = radar_data;
					
					if(radar_counter == radar_data_len){
						radar_prinf("goto footer\r\n");
						radar_counter=0;
						state = STATE_FOOTER;
					}
					break;
					
				case STATE_FOOTER:
					if(radar_counter==0 && radar_data==RECEIVE_FOOTER_1){
							radar_counter++;
						}else if(radar_counter==1 && radar_data==RECEIVE_FOOTER_2){
							radar_counter++;
						}else if(radar_counter==2 && radar_data==RECEIVE_FOOTER_3){
							radar_counter++;
						}else if(radar_counter==3 && radar_data==RECEIVE_FOOTER_4){
							radar_counter=0;
							radar_prinf("receive counter: %d, data: %X in footer\r\n",radar_counter,radar_data);
							radar_receive_ok_flag = 1;
						}
					break;
				
				default:
						state = STATE_IDLE;
          break;
			}
```