#ifndef __CONFIG_H
#define __CONFIG_H

#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_tim.h"

extern uint32_t esp32_return_data[6];
extern uint8_t target_status; 	   // Ŀ��״̬
extern uint16_t motion_distance;  // �˶�Ŀ�����
extern uint8_t motion_energy; 	   // �˶�Ŀ������ֵ
extern uint16_t static_distance;  // ��ֹĿ�����
extern uint8_t static_energy;     // ��ֹĿ������ֵ
extern uint8_t motion_gate_energy; // �˶�����������ֵ
extern uint8_t static_gate_energy; // ��ֹ����������ֵ
extern uint8_t light_value;
extern uint8_t engineer_state;

void deal_to_esp32_content(uint32_t *content);
void deal_esp32_return_content();
void radar_init_config(void);
void restart_radar(void);
void get_config_msg_radar(void);
void disable_engineer(void);
void single_config_radar(uint8_t *config,uint16_t len);
void deal_to_ld2412(uint8_t *content);


#endif
