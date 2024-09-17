#ifndef __RADAR_H
#define __RADAR_H	

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define RADAR_BUFFER_SIZE 100  // 假设数组长度为100

// 雷达使能配置和结束配置
extern uint8_t enable_config_radar[14];
extern uint8_t disable_config_radar[12];

// 雷达分辨率设置和读取
extern uint8_t radar_speed[22];
extern uint8_t read_speed[12];

// 基础设置和读取
extern uint8_t basic_config[17];
extern uint8_t read_basic_config[12];

// 工作模式使能和结束
extern uint8_t enable_work_model[12];
extern uint8_t disable_work_model[12];

// 运动灵敏度配置和查询
extern uint8_t action_ling_config[26];
extern uint8_t search_action_ling[12];

// 静止灵敏度配置和查询
extern uint8_t static_ling_config[26];
extern uint8_t search_static_ling[12];

// 动态背景校正和查询
extern uint8_t back[12];
extern uint8_t search_back[12];

// 固件信息查询、恢复出厂和重启
extern uint8_t read_hardware[12];
extern uint8_t new_out[14];
extern uint8_t restart[12];

// 蓝牙设置
extern uint8_t lanya[14];

// 光感辅助控制配置和查询
extern uint8_t light_config[13];
extern uint8_t search_light_config[12];

#endif
