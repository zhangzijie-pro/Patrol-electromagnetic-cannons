#include "radar.h"


// header(4)-len(2)-data(...)-tail(4)

const uint8_t radar_two_bit_len[2]={0x02,0x00};
const uint8_t radar_four_bit_len[2]={0x04,0x00};
const uint8_t radar_eight_bit_len[2]={0x08,0x00};
const uint8_t radar_seven_bit_len[2]={0x07,0x00};
const uint8_t radar_ten_bit_len[2]={0x10,0x00};

const uint8_t enable_config_radar[4] = {0xFF, 0x00, 0x01, 0x00};			// 使能配置
const uint8_t disable_config_radar[2] = {0xFE, 0x00};								// 结束配置

const uint8_t radar_speed[8] = {0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00};			// 雷达分辨率	6字节: [0:75cm距离门],[1:50cm距离门],[3:20cm距离门]
const uint8_t read_speed[2] = {0x11,0x00};															// 读取雷达分辨率

const uint8_t basic_config[7] = {0x02,0x00,0x01,0x0C,0x05,0x00,0x00};		// 基础设置	7byte 5字节: 一字节最小距离门,一字节最大距离门,两字节无人持续时间,1字节out输出0
const uint8_t read_basic_config[2] = {0x12,0x00};												// 读取基础设置

const uint8_t enable_engineer_model[2] = {0x62,0x00};											// 使能工作模式
const uint8_t disable_engineer_model[2] = {0x63,0x00};											// 结束工作模式

const uint8_t action_ling_config[16] = {0x03,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// 运动灵敏度配置
const uint8_t search_action_ling[2] = {0x13,0x00};											// 运动灵敏度查询

const uint8_t static_ling_config[16] = {0x04,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19};			// 静止灵敏度配置
const uint8_t search_static_ling[2] = {0x14,0x00};											// 静止灵敏度查询

const uint8_t back[2] = {0x0B,0x00};																		// 动态背景校正
const uint8_t search_back[2] = {0x1B,0x00};															// 动态背景校正进度查询

const uint8_t read_hardware[2] = {0xA0,0x00};														// 固件信息查询
const uint8_t new_out[2] = {0xA2,0x00};												// 恢复出厂
const uint8_t restart[2] = {0xA3,0x00};																	// 重启

const uint8_t lanya[4] = {0xA4,0x00,0x01,0x00};													// 蓝牙	0x01打开:0x00关闭

const uint8_t light_config[4] = {0x0C,0x00,0x01,0x50};												// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值
const uint8_t search_light_config[2] = {0x1C,0x00};													// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值

const uint8_t radar_header[4] = {0xFD, 0xFC, 0xFB, 0xFA};		// 数据头
const uint8_t radar_tail[4] = {0x04, 0x03, 0x02, 0x01};			// 数据尾


//RADAR_BUFFER_MAX_LEN
uint8_t radar_head_tail_Buffer[4]; // 处理接受的头尾数据
uint8_t radar_Serial_Buffer[50];
uint8_t radar_receive_ok_flag=0;
uint8_t radar_counter=0;
uint8_t radar_data;

void radar_usart_init(void)
{
		USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		// 配置 GPIO 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  // PA0 -> TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  //PA1 -> RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_UART4);
	
	
		USART_DeInit(UART4);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		// 配置 USART4 参数
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(UART4, &USART_InitStructure);

		// 使能 USART
    USART_Cmd(UART4, ENABLE);
		//USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);
		USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}



void UART4_IRQHandler(void){
		static int RxState = 0;
		if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET){
			radar_data = USART_ReceiveData(UART4);  // 接收数据
			if(RxState==0)	// 头数据对比
			{
					radar_head_tail_Buffer[radar_counter++] = radar_data;
					if(radar_counter==4){
						if(memcmp(radar_head_tail_Buffer,radar_header,sizeof(radar_header))==0){
							radar_counter=0;
							RxState=1;
						}
					}
			}else if(RxState==1){		// 先确定长度 在放入内容
					radar_Serial_Buffer[radar_counter++]=radar_data;
					uint8_t len = radar_Serial_Buffer[2]<<8|radar_Serial_Buffer[1];
					if(radar_counter>=len)
					{
							RxState=2;
							radar_counter=0;
					}
			}else if(RxState==2){
					radar_head_tail_Buffer[radar_counter++] = radar_data;
				
					if(radar_counter==4){
						if(memcmp(radar_head_tail_Buffer,radar_tail,sizeof(radar_tail))==0)
						{
							radar_counter=0;
							RxState=0;
							radar_receive_ok_flag=1;
						}
					}
			}
			USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		}
}


void radar_sendbyte(uint8_t Byte){
	while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));
	USART_SendData(UART4,Byte);
}

void radar_sendArray(const uint8_t *Array, uint16_t len)
{
	for(uint16_t i=0;i<len;i++){
		radar_sendbyte(Array[i]);
	}
}

void radar_sendString(char *String)
{
	while(*String!='\0')
	{
		while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));
		USART_SendData(UART4,*String++);
	}
}

void radar_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	radar_sendString(String);
}

// 配置雷达信息
void radar_setting(uint8_t bit, uint8_t *msg){
	switch(bit){
		case 2:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_two_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
			case 4:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_four_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
			case 7:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_seven_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 8:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_eight_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
		case 10:
				radar_sendArray(radar_header,4);	// 发送头
				radar_sendArray(radar_ten_bit_len,2);					// 发送长度
				radar_sendArray(msg,bit);					// 发送内容
				radar_sendArray(radar_tail,4);		// 发送尾
			break;
	}
}