#include "config.h"
#include "radar.h"

// header(4)-len(2)-data(...)-tail(4)

const uint8_t radar_two_bit_len[2]={0x02,0x00};
const uint8_t radar_four_bit_len[2]={0x04,0x00};
const uint8_t radar_eight_bit_len[2]={0x08,0x00};
const uint8_t radar_seven_bit_len[2]={0x07,0x00};
const uint8_t radar_16_bit_len[2]={0x10,0x00};

const uint8_t enable_config_radar[4] = {0xFF, 0x00, 0x01, 0x00};			// ʹ������
const uint8_t disable_config_radar[2] = {0xFE, 0x00};								// ��������

// radar_speed[2]  00:75cm  01:50cm  03: 20cm
const uint8_t radar_speed[8] = {0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00};			// �״�ֱ���	6�ֽ�: [0:75cm������],[1:50cm������],[3:20cm������]
const uint8_t read_speed[2] = {0x11,0x00};															// ��ȡ�״�ֱ���

const uint8_t basic_config[7] = {0x02,0x00,0x01,0x0C,0x05,0x00,0x00};		// ��������	7byte 5�ֽ�: һ�ֽ���С������,һ�ֽ���������,���ֽ����˳���ʱ��,1�ֽ�out���0
const uint8_t read_basic_config[2] = {0x12,0x00};												// ��ȡ��������

const uint8_t enable_engineer_model[2] = {0x62,0x00};											// ʹ�ܹ���ģʽ
const uint8_t disable_engineer_model[2] = {0x63,0x00};											// ��������ģʽ

const uint8_t action_ling_config[16] = {0x03,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// �˶�����������
const uint8_t search_action_ling[2] = {0x13,0x00};											// �˶������Ȳ�ѯ

const uint8_t static_ling_config[16] = {0x04,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// ��ֹ����������
const uint8_t search_static_ling[2] = {0x14,0x00};											// ��ֹ�����Ȳ�ѯ

const uint8_t back[2] = {0x0B,0x00};																		// ��̬����У��
const uint8_t search_back[2] = {0x1B,0x00};															// ��̬����У�����Ȳ�ѯ

const uint8_t read_hardware[2] = {0xA0,0x00};														// �̼���Ϣ��ѯ
const uint8_t new_out[2] = {0xA2,0x00};												// �ָ�����
const uint8_t restart[2] = {0xA3,0x00};																	// ����

const uint8_t lanya[4] = {0xA4,0x00,0x01,0x00};													// ����	0x01��:0x00�ر�

const uint8_t light_config[4] = {0x0C,0x00,0x01,0x50};												// ��и������� 0x01: 0x00�ر�,0x01С����ֵ(0x0C:0x00~0xFF),0x02������ֵ
const uint8_t search_light_config[2] = {0x1C,0x00};													// ��и������� 0x01: 0x00�ر�,0x01С����ֵ(0x0C:0x00~0xFF),0x02������ֵ

const uint8_t radar_header[4] = {0xFD, 0xFC, 0xFB, 0xFA};		// ����ͷ
const uint8_t radar_tail[4] = {0x04, 0x03, 0x02, 0x01};			// ����β

//* �������� 
//* 1.esp32-cam -> stm32f4: Usart		9�ֽڱ��� -> 6�ֽ�data
uint32_t esp32_return_data[6];

void deal_to_esp32_content(uint32_t *content)
{
	int len= sizeof(content);
	// �жϱ��ĳ���, ���ֽڵ�֡ͷ��֡β
	if(len==8&&content[0]==content[1]&&content[7]&&!content[8])
	{
		esp32_return_data[0] = 0x01;					// ��־λ�Ƿ�Ϊ��Ч����
		
		esp32_return_data[1] = content[2];		// �Ƿ��⵽����
		// x,y,w,h����
		esp32_return_data[2] = content[3];
		esp32_return_data[3] = content[4];
		esp32_return_data[4] = content[5];
		esp32_return_data[5] = content[6];
		
	}else{
		esp32_return_data[0] = 0x00;
	}
}

void deal_esp32_return_content(){
	if(esp32_return_data[0]==0x01)		// ������Ч����
	{
		if(esp32_return_data[1]==0x01)			// ��⵽���������
		{
			// ���������ƶ�����ڵ�ָ��λ��....
		}else if(esp32_return_data[1]==0x00)	// �޼�⵽����
		{
			// �����������䷶Χ������....
		}
	}else if(esp32_return_data[0]==0x00)
	{
		// ��Ч���ݴ���
		// pass
	}
}

/*************************
     
			�״���������

************************/
// �����״���Ϣ
void radar_setting(uint8_t bit, const uint8_t *msg){
	switch(bit){
		case 2:
				radar_sendArray(radar_header,4);	// ����ͷ
				radar_sendArray(radar_two_bit_len,2);					// ���ͳ���
				radar_sendArray(msg,bit);					// ��������
				radar_sendArray(radar_tail,4);		// ����β
			break;
		case 4:
				radar_sendArray(radar_header,4);	// ����ͷ
				radar_sendArray(radar_four_bit_len,2);					// ���ͳ���
				radar_sendArray(msg,bit);					// ��������
				radar_sendArray(radar_tail,4);		// ����β
			break;
		case 7:
				radar_sendArray(radar_header,4);	// ����ͷ
				radar_sendArray(radar_seven_bit_len,2);					// ���ͳ���
				radar_sendArray(msg,bit);					// ��������
				radar_sendArray(radar_tail,4);		// ����β
			break;
		case 8:
				radar_sendArray(radar_header,4);	// ����ͷ
				radar_sendArray(radar_eight_bit_len,2);					// ���ͳ���
				radar_sendArray(msg,bit);					// ��������
				radar_sendArray(radar_tail,4);		// ����β
			break;
		case 16:
				radar_sendArray(radar_header,4);	// ����ͷ
				radar_sendArray(radar_16_bit_len,2);					// ���ͳ���
				radar_sendArray(msg,bit);					// ��������
				radar_sendArray(radar_tail,4);		// ����β
			break;
	}
}
uint8_t enable_config=1;
uint8_t engineer_state=0;

void radar_enable_config(){
	enable_config=1;
	// ʹ���״�
	radar_setting(4,enable_config_radar);
}

void radar_disable_config(){
	// �����״�����
	radar_setting(4,disable_config_radar);

}

void new_radar(){
	radar_enable_config();
	radar_setting(2,new_out);
	radar_disable_config();
}

// ����
void restart_radar(){
	radar_enable_config();
	radar_setting(2,restart);
	radar_disable_config();
}

// ��������ģʽ
void start_engineer(){
	radar_enable_config();
	radar_setting(2,enable_engineer_model);
	engineer_state=1;
	radar_disable_config();
}


uint8_t target_status; 	   // Ŀ��״̬
uint16_t motion_distance;  // �˶�Ŀ�����
uint8_t motion_energy; 	   // �˶�Ŀ������ֵ
uint16_t static_distance;  // ��ֹĿ�����
uint8_t static_energy;     // ��ֹĿ������ֵ
uint8_t motion_gate_energy; // �˶�����������ֵ
uint8_t static_gate_energy; // ��ֹ����������ֵ
uint8_t light_value;

//* ����LD2412�״ﷵ������(����ģʽ����)
void deal_to_ld2412(uint8_t *content){
	if(content[0]==0xF4&&content[1]==0xF3&&content[2]==0xF2&&content[3]==0xF1)
	{
		uint8_t data_type = content[4]; // ��������
		if(data_type==0x01)
		{
			target_status = content[6];		
			// 0x00: ��Ŀ�� , 0x01: �˶�Ŀ�� , 0x02: ��ֹĿ�� , 0x03: �˶�&��ֹĿ��
			motion_distance = (content[7]<<8)|content[8];
			motion_energy = content[9];
			static_distance = (content[10]<<8)|content[11];
			static_energy = content[12];
			
			int index = 13;
        while(index < 27) { // ������14��������		10m
            motion_gate_energy = content[index];
            static_gate_energy = content[index + 1];
            index += 2;
            // ����ÿ�������ŵ�����ֵ
						// �������״�ͼ����ʾ
				}  
      // ��ȡ��в���ֵ
      light_value = content[27];  // ��в���ֵ
		}
	}
}
