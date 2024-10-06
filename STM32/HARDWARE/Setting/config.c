#include "config.h"


// header(4)-len(2)-data(...)-tail(4)
// 单位都是cm
#define DISTANCE_STEP_CM 50		// 门距离
#define XL_POS  5
#define XR_POS -5
#define M_PI 3.14159265358979323846


const uint8_t radar_two_bit_len[2]={0x02,0x00};
const uint8_t radar_four_bit_len[2]={0x04,0x00};
const uint8_t radar_eight_bit_len[2]={0x08,0x00};
const uint8_t radar_seven_bit_len[2]={0x07,0x00};
const uint8_t radar_16_bit_len[2]={0x10,0x00};

const uint8_t enable_config_radar[4] = {0xFF, 0x00, 0x01, 0x00};			// 使能配置
const uint8_t disable_config_radar[2] = {0xFE, 0x00};								// 结束配置

// radar_speed[2]  00:75cm  01:50cm  03: 20cm
const uint8_t radar_speed[8] = {0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00};			// 雷达分辨率	6字节: [0:75cm距离门],[1:50cm距离门],[3:20cm距离门]
const uint8_t read_speed[2] = {0x11,0x00};															// 读取雷达分辨率

const uint8_t basic_config[7] = {0x02,0x00,0x01,0x0C,0x05,0x00,0x00};		// 基础设置	7byte 5字节: 一字节最小距离门,一字节最大距离门,两字节无人持续时间,1字节out输出0
const uint8_t read_basic_config[2] = {0x12,0x00};												// 读取基础设置

const uint8_t enable_engineer_model[2] = {0x62,0x00};											// 使能工作模式
const uint8_t disable_engineer_model[2] = {0x63,0x00};											// 结束工作模式

const uint8_t action_ling_config[16] = {0x03,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// 运动灵敏度配置
const uint8_t search_action_ling[2] = {0x13,0x00};											// 运动灵敏度查询

const uint8_t static_ling_config[16] = {0x04,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// 静止灵敏度配置
const uint8_t search_static_ling[2] = {0x14,0x00};											// 静止灵敏度查询

const uint8_t back[2] = {0x0B,0x00};																		// 动态背景校正
const uint8_t search_back[2] = {0x1B,0x00};															// 动态背景校正进度查询

const uint8_t read_hardware[2] = {0xA0,0x00};														// 固件信息查询
const uint8_t new_out[2] = {0xA2,0x00};												// 恢复出厂
const uint8_t restart[2] = {0xA3,0x00};																	// 重启

const uint8_t lanya[4] = {0xA4,0x00,0x01,0x00};													// 蓝牙	0x01打开:0x00关闭

const uint8_t light_config[4] = {0x0C,0x00,0x01,0x50};												// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值
const uint8_t search_light_config[2] = {0x1C,0x00};													// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值

const uint8_t radar_header[4] = {0xFD, 0xFC, 0xFB, 0xFA};		// 数据头
const uint8_t radar_tail[4] = {0x04, 0x03, 0x02, 0x01};			// 数据尾


/***************************************************************************
     
											esp32解析报文 
			1.esp32-cam -> stm32f4: Usart		8字节报文 -> 6字节data
					0xAA 0x01 0x01 0x00 0x00 0x00 0x00 0xFF

***************************************************************************/

void deal_esp32_return_content(uint8_t *content){
	if(content[0]==0x01)		// 传回是否为有效数据
	{
		esp_prinf("有效数据");
		if(content[1]==0x01)			// 检测到有人体存在
		{
			// 根据坐标调整电磁炮到指定位置....
			esp_prinf("人体存在");
		}
		else if(content[1]==0x00)	// 无检测到人体
		{
			// 更换武器发射范围性内容....
			esp_prinf("无检测到人体");
		}
		else if(content[1]==0x02)
		{
			// 检测到多人目标
			esp_prinf("多人目标");
		}
	}else if(content[0]==0x00)
	{
		// 无效数据处理
		// pass
		esp_prinf("无效数据");
	}
}

void clear_content(uint8_t *content){
	uint8_t len = sizeof(content);
	for(uint8_t i=0;i<len;i++) content[i]=0;
}

/*************************
     
			雷达配 置内容
			LD2412 LD2450

************************/

// 配置雷达信息
void radar_setting(uint8_t bit, const uint8_t *msg){
	switch(bit){
		case 2:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_two_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 4:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_four_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 7:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_seven_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 8:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_eight_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 16:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_16_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
	}
}
uint8_t enable_config=0;
uint8_t engineer_state=0;

void radar_enable_config(){
	enable_config=1;
	// 使能雷达
	radar_setting(4,enable_config_radar);
}

void radar_disable_config(){
	// 结束雷达配置
	radar_setting(4,disable_config_radar);

}

#if LD_MODE
void radar_init_config(void){
	radar_enable_config();
	
	// 设置分辨率   	0:75cm  --  1:50cm -- 3:25cm
	//radar_speed[4]=0x01;
	radar_setting(8,radar_speed);
	
	// 设置运动和静止的灵敏度
	radar_setting(16,action_ling_config);
	radar_setting(16,static_ling_config);
	
	radar_disable_config();
}

// 重启
void restart_radar(){
	radar_enable_config();
	radar_setting(2,restart);
	radar_disable_config();
}

// 开启工程模式
void start_engineer(){
	radar_enable_config();
	delay_ms(1000);
	radar_setting(2,enable_engineer_model);
	engineer_state=1;
	delay_ms(1000);
	radar_disable_config();
}


uint8_t target_status; 	   // 目标状态
uint8_t motion_distance;  // 运动目标距离
uint8_t motion_energy; 	   // 运动目标能量值
uint8_t static_distance;  // 静止目标距离
uint8_t static_energy;     // 静止目标能量值
uint8_t movingTargetZone=0;
uint8_t stationaryTargetZone=0;


//* 解析LD2412雷达返回数据(工作  工程模式数据)
//  0B 00 02 AA 02 51 00 00 00 00 3B 55 00  工作 
//  2B 00 01 AA 02 00 00 00 64 00 64 0D 0D 00 00 00 00 00 00 00 00 01 01 01 01 00 00 00 64 64 64 13 64 64 64 64 5F 08 02 02 05 4C 00 55 00 工程模式
void deal_to_ld2412(uint8_t *data, uint8_t *target_status,uint8_t *movingTargetDistance, uint8_t *movingTargetZone, uint8_t *stationaryTargetDistance, uint8_t *stationaryTargetZone){
		*target_status = data[4];
		if(data[0]==0x2B){
			   // 运动目标距离（第8、9字节，小端格式）
				*movingTargetDistance = (data[6] << 8) | data[5];

				// 静止目标距离（第12、13字节，小端格式）
				*stationaryTargetDistance = (data[8] << 8) | data[7];

				// 根据距离计算运动目标在哪个区间
				if (*movingTargetDistance > 0) {
						*movingTargetZone = (*movingTargetDistance + DISTANCE_STEP_CM - 1) / DISTANCE_STEP_CM; // 区间从1开始
				} else {
						*movingTargetZone = 0; // 没有运动目标
				}

				// 根据距离计算静止目标在哪个区间
				if (*stationaryTargetDistance > 0) {
						*stationaryTargetZone = (*stationaryTargetDistance + DISTANCE_STEP_CM - 1) / DISTANCE_STEP_CM; // 区间从1开始
				} else {
						*stationaryTargetZone = 0; // 没有静止目标
				}
		}else if(data[0]==0x0B){
				*movingTargetDistance = (data[7] << 8) | data[8];

					// 静止目标距离（第8、9字节，小端格式）
				*stationaryTargetDistance = (data[11] << 8) | data[10];
			
					// 根据距离计算运动目标在哪个区间
				if (*movingTargetDistance > 0) {
						*movingTargetZone = (*movingTargetDistance + DISTANCE_STEP_CM - 1) / DISTANCE_STEP_CM; // 区间从1开始
				} else {
						*movingTargetZone = 0; // 没有运动目标
				}

				// 根据距离计算静止目标在哪个区间
				if (*stationaryTargetDistance > 0) {
						*stationaryTargetZone = (*stationaryTargetDistance + DISTANCE_STEP_CM - 1) / DISTANCE_STEP_CM; // 区间从1开始
				} else {
						*stationaryTargetZone = 0; // 没有静止目标
				}
		}
}

void return_target_state(void){
		switch(target_status){
			case 0:
				esp_prinf("没有发现目标");
				break;
			case 1:
				esp_prinf("发现运动目标");
				break;
			case 2:
				esp_prinf("发现静止目标");
				break;
			case 3:
				esp_prinf("发现运动与静止目标");
				break;
			default:
				esp_prinf("发现没有目标");
				break;
		}
}

// 检测区间 1~13
uint8_t Detection_interval(){
	if((movingTargetZone==0)&&(stationaryTargetZone==0)){
		return 0;
	}else if((movingTargetZone!=0)&&(stationaryTargetZone==0))
	{
		return movingTargetZone;
	}else if((movingTargetZone==0)&&(stationaryTargetZone!=0))
	{
		return stationaryTargetZone;
	}else if((movingTargetZone!=0)&&(stationaryTargetZone!=0))
	{
		return (movingTargetZone+stationaryTargetZone)/2;
	}
}

/*************************
     
			计算目标角度

************************/

// (x-x1)^2+y^2=r1^2  	(x-x2)^2+y^2=r2^2
// x1: (XL_POS,0)   x2: (XR_POS,0)
// r1 = LEFT_Zone*DISTANCE_STEP_CM;	r2 = RIGHT_Zone*DISTANCE_STEP_CM
uint8_t quadrant;		// 象限

double Get_Angle_from_radar(){
	// 左边传感器距离
	uint8_t left_interval = Detection_interval();
	// 右边传感器距离
	// need change
	uint8_t right_interval = 4;
	double r1 = left_interval*DISTANCE_STEP_CM;
	double r2 = right_interval*DISTANCE_STEP_CM;
	double x1 = XL_POS, x2 = XR_POS;
	double c = r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2;
	
	// 解出 x
	double x = (c) / (2 * (x2 - x1));

	if(x>0) quadrant=1; else quadrant=2;
	double y = sqrt(r1 * r1 - (x - x1) * (x - x1));
	
  double tan_value = fabs(x/y);	//得到角度夹角的值
  double angle = atan(tan_value) * (180.0 / M_PI);
	
	if(quadrant==1) angle = angle+90;
	else if(quadrant==2) angle = 90-angle;
	
	return angle;
}

#else
/*************************************************
     
										LD2450

target_one   目标1信息
target_two 	 目标2信息
target_three 目标3信息
************************************************/

void deal_ld2450_data(uint8_t *target, Target_msg *msg){
	// 单位: mm
	msg->X_pos = target_one[0]|(target_one[1]<<8);
	msg->Y_pos = target_one[2]|(target_one[3]<<8);
	if(target_one[1]&0x80){
		msg->X_pos -= 0x8000;
		msg->Y_pos -= 0x8000;
	}else{
		msg->Y_pos -= 0x8000;
	}
	msg->Zone = target[6]+target[7]*256;
	// 角度: float
	msg->Angle = return_angle(msg->X_pos,msg->Y_pos);
}

// 返回舵机角度
float return_angle(int16_t x,int16_t y)
{
	double angle = atan2(y,x);
	
	double target_angle = angle*(180.0/M_PI);
	if(angle>0)
	{
		return (float)(target_angle+90.0);
	}else if(angle<0){
		return (float)(90.0-target_angle);
	}
}

#endif
