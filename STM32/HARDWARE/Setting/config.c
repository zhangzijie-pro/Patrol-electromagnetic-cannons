#include "config.h"
#include "radar.h"

// header(4)-len(2)-data(...)-tail(4)

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

//* 解析报文 
//* 1.esp32-cam -> stm32f4: Usart		9字节报文 -> 6字节data
uint32_t esp32_return_data[6];

void deal_to_esp32_content(uint32_t *content)
{
	int len= sizeof(content);
	// 判断报文长度, 两字节的帧头和帧尾
	if(len==8&&content[0]==content[1]&&content[7]&&!content[8])
	{
		esp32_return_data[0] = 0x01;					// 标志位是否为有效数据
		
		esp32_return_data[1] = content[2];		// 是否检测到有人
		// x,y,w,h坐标
		esp32_return_data[2] = content[3];
		esp32_return_data[3] = content[4];
		esp32_return_data[4] = content[5];
		esp32_return_data[5] = content[6];
		
	}else{
		esp32_return_data[0] = 0x00;
	}
}

void deal_esp32_return_content(){
	if(esp32_return_data[0]==0x01)		// 传回有效数据
	{
		if(esp32_return_data[1]==0x01)			// 检测到有人体存在
		{
			// 根据坐标移动电磁炮到指定位置....
		}else if(esp32_return_data[1]==0x00)	// 无检测到人体
		{
			// 更换武器发射范围性内容....
		}
	}else if(esp32_return_data[0]==0x00)
	{
		// 无效数据处理
		// pass
	}
}

/*************************
     
			雷达配置内容

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
uint8_t enable_config=1;
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

void new_radar(){
	radar_enable_config();
	radar_setting(2,new_out);
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
	radar_setting(2,enable_engineer_model);
	engineer_state=1;
	radar_disable_config();
}


uint8_t target_status; 	   // 目标状态
uint16_t motion_distance;  // 运动目标距离
uint8_t motion_energy; 	   // 运动目标能量值
uint16_t static_distance;  // 静止目标距离
uint8_t static_energy;     // 静止目标能量值
uint8_t motion_gate_energy; // 运动距离门能量值
uint8_t static_gate_energy; // 静止距离门能量值
uint8_t light_value;

//* 解析LD2412雷达返回数据(工程模式数据)
void deal_to_ld2412(uint8_t *content){
	if(content[0]==0xF4&&content[1]==0xF3&&content[2]==0xF2&&content[3]==0xF1)
	{
		uint8_t data_type = content[4]; // 数据类型
		if(data_type==0x01)
		{
			target_status = content[6];		
			// 0x00: 无目标 , 0x01: 运动目标 , 0x02: 静止目标 , 0x03: 运动&静止目标
			motion_distance = (content[7]<<8)|content[8];
			motion_energy = content[9];
			static_distance = (content[10]<<8)|content[11];
			static_energy = content[12];
			
			int index = 13;
        while(index < 27) { // 假设有14个距离门		10m
            motion_gate_energy = content[index];
            static_gate_energy = content[index + 1];
            index += 2;
            // 处理每个距离门的能量值
						// 更新在雷达图上显示
				}  
      // 读取光感测量值
      light_value = content[27];  // 光感测量值
		}
	}
}
