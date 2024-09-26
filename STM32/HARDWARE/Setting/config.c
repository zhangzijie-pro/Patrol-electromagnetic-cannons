#include "config.h"
#include "radar.h"

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

uint8_t engineer_state = 0;

void radar_init_config(void){
	radar_usart_init();	// ��ʼ����������
	
	// ʹ���״�
	radar_sendArray(enable_config_radar,14);
	
	// ���÷ֱ���   	0:75cm  --  1:50cm -- 3:25cm
	//radar_speed[4]=0x01;
	
	radar_sendArray(radar_speed,22);
	// ��ȡ�ֱ���
	//radar_sendArray(read_speed,12);
	
	// ʹ�ܹ���ģʽ
	radar_sendArray(enable_engineer_model,12);
	engineer_state = 1;
	
	// �����˶��;�ֹ��������
	radar_sendArray(action_ling_config,26);
	radar_sendArray(static_ling_config,26);
	
	// ���ù�и���
	radar_sendArray(light_config,13);
	
	// �����״�����
	radar_sendArray(disable_config_radar,12);
}

// �����״�
void restart_radar(void)
{
	radar_sendArray(restart,12);
}

// ��ȡӲ����Ϣ
void get_config_msg_radar(void){
	radar_sendArray(read_hardware,12);
}

// �رչ���ģʽ
void disable_engineer(void){
	radar_sendArray(disable_engineer_model,12);
	engineer_state=0;
}

// ��һ�����״�����
void single_config_radar(uint8_t *config,uint16_t len)
{
	radar_sendArray(config,len);
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
