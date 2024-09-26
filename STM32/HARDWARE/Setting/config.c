#include "config.h"
#include "radar.h"

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

uint8_t engineer_state = 0;

void radar_init_config(void){
	radar_usart_init();	// 初始化串口内容
	
	// 使能雷达
	radar_sendArray(enable_config_radar,14);
	
	// 设置分辨率   	0:75cm  --  1:50cm -- 3:25cm
	//radar_speed[4]=0x01;
	
	radar_sendArray(radar_speed,22);
	// 读取分辨率
	//radar_sendArray(read_speed,12);
	
	// 使能工程模式
	radar_sendArray(enable_engineer_model,12);
	engineer_state = 1;
	
	// 设置运动和静止的灵敏度
	radar_sendArray(action_ling_config,26);
	radar_sendArray(static_ling_config,26);
	
	// 设置光感辅助
	radar_sendArray(light_config,13);
	
	// 结束雷达配置
	radar_sendArray(disable_config_radar,12);
}

// 重启雷达
void restart_radar(void)
{
	radar_sendArray(restart,12);
}

// 读取硬件信息
void get_config_msg_radar(void){
	radar_sendArray(read_hardware,12);
}

// 关闭工程模式
void disable_engineer(void){
	radar_sendArray(disable_engineer_model,12);
	engineer_state=0;
}

// 单一设置雷达内容
void single_config_radar(uint8_t *config,uint16_t len)
{
	radar_sendArray(config,len);
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
