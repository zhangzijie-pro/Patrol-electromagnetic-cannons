#include "usart.h"

uint8_t enable_config_radar[] = {0xFD, 0xFC, 0xFB, 0xFA, 0x04, 0x00, 0xFF, 0x00, 0x01, 0x00, 0x04, 0x03, 0x02, 0x01};			// 使能配置
uint8_t disable_config_radar[] = {0xFD, 0xFC, 0xFB, 0xFA, 0x02, 0x00, 0xFE, 0x00, 0x04, 0x03, 0x02, 0x01};								// 结束配置

uint8_t radar_speed[] = {0xFD, 0xFC, 0xFB, 0xFA,0x08,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00, 0x04, 0x03, 0x02, 0x01, 0x04, 0x03, 0x02, 0x01};			// 雷达分辨率	6字节: [0:75cm距离门],[1:50cm距离门],[3:20cm距离门]
uint8_t read_speed[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x11,0x00, 0x04, 0x03, 0x02, 0x01};																		// 读取雷达分辨率

uint8_t basic_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x07,0x00,0x02,0x00,0x01,0x0C,0x05,0x00,0x00, 0x04, 0x03, 0x02, 0x01};					// 基础设置	5字节: 一字节最小距离门,一字节最大距离门,两字节无人持续时间,1字节out输出0
uint8_t read_basic_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x12,0x00, 0x04, 0x03, 0x02, 0x01};															// 读取基础设置

uint8_t enable_work_model[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x62,0x00, 0x04, 0x03, 0x02, 0x01};															// 使能工作模式
uint8_t disable_work_model[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x63,0x00, 0x04, 0x03, 0x02, 0x01};														// 结束工作模式

uint8_t action_ling_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x10,0x00,0x03,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19, 0x04, 0x03, 0x02, 0x01};			// 运动灵敏度配置
uint8_t search_action_ling[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x13,0x00, 0x04, 0x03, 0x02, 0x01};															// 运动灵敏度查询

uint8_t static_ling_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x10,0x00,0x04,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19, 0x04, 0x03, 0x02, 0x01};			// 静止灵敏度配置
uint8_t search_static_ling[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x14,0x00, 0x04, 0x03, 0x02, 0x01};															// 静止灵敏度查询

uint8_t back[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x0B,0x00, 0x04, 0x03, 0x02, 0x01};															// 动态背景校正
uint8_t search__back[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x1B,0x00, 0x04, 0x03, 0x02, 0x01};															// 动态背景校正进度查询

uint8_t read_hardware[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0xA0,0x00, 0x04, 0x03, 0x02, 0x01};															// 固件信息查询
uint8_t new_out[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0xA2,0x01,0x00,0x00, 0x04, 0x03, 0x02, 0x01};													// 恢复出厂
uint8_t restart[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0xA3,0x00, 0x04, 0x03, 0x02, 0x01};																		// 重启

uint8_t lanya[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0xA4,0x00,0x01,0x00, 0x04, 0x03, 0x02, 0x01};													// 蓝牙	0x01打开:0x00关闭

uint8_t light_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0x0C,0x01,0x50, 0x04, 0x03, 0x02, 0x01};													// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值
uint8_t search_light_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x1C, 0x04, 0x03, 0x02, 0x01};													// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值



