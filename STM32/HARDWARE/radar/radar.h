#ifndef __RADAR_H
#define __RADAR_H	

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// HEX
// �����������ݳ���
extern const uint8_t radar_four_bit_len[2];
extern const uint8_t radar_two_bit_len[2];
extern const uint8_t radar_eight_bit_len[2];
extern const uint8_t radar_seven_bit_len[2];
extern const uint8_t radar_ten_bit_len[2];

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

//RADAR_BUFFER_MAX_LEN
extern uint8_t radar_Serial_Buffer[];
extern uint8_t radar_counter;
extern uint8_t radar_data;


void radar_usart_init(void);
void radar_sendbyte(uint8_t Byte);
void radar_sendArray(const uint8_t *Array, uint16_t len);
void radar_sendString(char *String);
void radar_prinf(char *format,...);

int radar_GetFlag();
#endif
