#ifndef __RADAR_H
#define __RADAR_H	

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define RADAR_BUFFER_SIZE 100  // �������鳤��Ϊ100

// �״�ʹ�����úͽ�������
extern uint8_t enable_config_radar[14];
extern uint8_t disable_config_radar[12];

// �״�ֱ������úͶ�ȡ
extern uint8_t radar_speed[22];
extern uint8_t read_speed[12];

// �������úͶ�ȡ
extern uint8_t basic_config[17];
extern uint8_t read_basic_config[12];

// ����ģʽʹ�ܺͽ���
extern uint8_t enable_work_model[12];
extern uint8_t disable_work_model[12];

// �˶����������úͲ�ѯ
extern uint8_t action_ling_config[26];
extern uint8_t search_action_ling[12];

// ��ֹ���������úͲ�ѯ
extern uint8_t static_ling_config[26];
extern uint8_t search_static_ling[12];

// ��̬����У���Ͳ�ѯ
extern uint8_t back[12];
extern uint8_t search_back[12];

// �̼���Ϣ��ѯ���ָ�����������
extern uint8_t read_hardware[12];
extern uint8_t new_out[14];
extern uint8_t restart[12];

// ��������
extern uint8_t lanya[14];

// ��и����������úͲ�ѯ
extern uint8_t light_config[13];
extern uint8_t search_light_config[12];

#endif
