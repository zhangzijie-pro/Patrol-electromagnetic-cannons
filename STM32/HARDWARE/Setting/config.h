#ifndef __CONFIG_H
#define __CONFIG_H

#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_tim.h"

extern uint8_t enable_config;
extern uint8_t engineer_state;

// HEX
// �����������ݳ���
extern const uint8_t radar_four_bit_len[2];
extern const uint8_t radar_two_bit_len[2];
extern const uint8_t radar_eight_bit_len[2];
extern const uint8_t radar_seven_bit_len[2];
extern const uint8_t radar_16_bit_len[2];

// �״�ʹ�����úͽ�������
extern const uint8_t enable_config_radar[4];
extern const uint8_t disable_config_radar[2];

// �״�ֱ������úͶ�ȡ
extern const uint8_t radar_speed[8];
extern const uint8_t read_speed[2];

// �������úͶ�ȡ
extern const uint8_t basic_config[7];
extern const uint8_t read_basic_config[2];

// ����ģʽʹ�ܺͽ���
extern const uint8_t enable_engineer_model[2];
extern const uint8_t disable_engineer_model[2];

// �˶����������úͲ�ѯ
extern const uint8_t action_ling_config[16];
extern const uint8_t search_action_ling[2];

// ��ֹ���������úͲ�ѯ
extern const uint8_t static_ling_config[16];
extern const uint8_t search_static_ling[2];

// ��̬����У���Ͳ�ѯ
extern const uint8_t back[2];
extern const uint8_t search_back[2];

// �̼���Ϣ��ѯ���ָ�����������
extern const uint8_t read_hardware[2];
extern const uint8_t new_out[2];
extern const uint8_t restart[2];

// ��������
extern const uint8_t lanya[4];

// ��и����������úͲ�ѯ
extern const uint8_t light_config[4];
extern const uint8_t search_light_config[2];

extern const uint8_t radar_header[4];		// ����ͷ
extern const uint8_t radar_tail[4];			// ����β


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


// esp32 content
void deal_to_esp32_content(uint32_t *content);
void deal_esp32_return_content();


// radar
void radar_setting(uint8_t bit, const uint8_t *msg);
void radar_enable_config();
void radar_disable_config();
void restart_radar();
void start_engineer();
void new_radar();
void deal_to_ld2412(uint8_t *content);

#endif
