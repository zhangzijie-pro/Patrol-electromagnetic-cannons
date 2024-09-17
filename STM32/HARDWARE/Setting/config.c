#include "config.h"

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

uint8_t target_status; 	   // Ŀ��״̬
uint16_t motion_distance;  // �˶�Ŀ�����
uint8_t motion_energy; 	   // �˶�Ŀ������ֵ
uint16_t static_distance;  // ��ֹĿ�����
uint8_t static_energy;     // ��ֹĿ������ֵ
uint8_t motion_gate_energy; // �˶�����������ֵ
uint8_t static_gate_energy; // ��ֹ����������ֵ
uint8_t light_value;

//* ����LD2412�״ﷵ������
void deal_to_ld2412(uint8_t content){
	
}