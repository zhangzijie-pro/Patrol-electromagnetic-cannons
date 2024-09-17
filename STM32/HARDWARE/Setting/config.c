#include "config.h"

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

uint8_t target_status; 	   // 目标状态
uint16_t motion_distance;  // 运动目标距离
uint8_t motion_energy; 	   // 运动目标能量值
uint16_t static_distance;  // 静止目标距离
uint8_t static_energy;     // 静止目标能量值
uint8_t motion_gate_energy; // 运动距离门能量值
uint8_t static_gate_energy; // 静止距离门能量值
uint8_t light_value;

//* 解析LD2412雷达返回数据
void deal_to_ld2412(uint8_t content){
	
}