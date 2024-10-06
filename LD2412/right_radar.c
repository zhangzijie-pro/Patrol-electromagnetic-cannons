#include "right_radar.h"
#include "config.h"


#define RECEIVE_HEADER_1 0xF4
#define RECEIVE_HEADER_2 0xF3
#define RECEIVE_HEADER_3 0xF2
#define RECEIVE_HEADER_4 0xF1

#define RECEIVE_FOOTER_1 0xF8
#define RECEIVE_FOOTER_2 0xF7
#define RECEIVE_FOOTER_3 0xF6
#define RECEIVE_FOOTER_4 0xF5


uint8_t right_radar_Serial_Buffer[50];
uint8_t right_radar_receive_ok_flag=0;
uint8_t right_radar_counter;
uint8_t right_data_len;

void Get_right_data_len(){
	right_data_len = (0x00<<8|0x0B)+2;
	if(right_radar_Serial_Buffer[0]==0x2B){
		right_data_len = (0x00<<8|0x2B)+2;
	}
}

void right_radar_init(){
	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PC12 -> TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  //PD2 -> RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
	
	USART_DeInit(UART5);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	// ???? USART4 ????
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(UART5, &USART_InitStructure);


	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	
			// ??? USART
	USART_Cmd(UART5, ENABLE);
}

void UART5_IRQHandler(void){
	static uint8_t RxState =0;
	static uint8_t pRxPacket=0;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){
			uint8_t radar_data = USART_ReceiveData(UART5);

				if(RxState==0){
					if(radar_data==RECEIVE_HEADER_1){
						RxState=1;
					}
				}else if(RxState==1){
					if(radar_data == RECEIVE_HEADER_2){
						RxState=2;
					}else{
						RxState=0;
					}
				}
				else if(RxState==2){
					if(radar_data == RECEIVE_HEADER_3){
						RxState=3;
					}else{
						RxState=0;
					}
				}
				else if(RxState==3){ // ???????
					if(radar_data == RECEIVE_HEADER_4){
						RxState=4;
					}else{
						RxState=0;
					}
				}else if(RxState==4){
					right_radar_Serial_Buffer[pRxPacket] = radar_data;
					pRxPacket++;
					if(pRxPacket>=right_data_len){
						RxState=5;
						pRxPacket=0;
					}
				}else if(RxState==5){
					if(radar_data == RECEIVE_FOOTER_1){
						RxState=6;
					}else{
						RxState=0;
					}
				}else if(RxState==6){
					if(radar_data == RECEIVE_FOOTER_2){
						RxState=7;
					}else{
						RxState=0;
					}
				}else if(RxState==7){
					if(radar_data == RECEIVE_FOOTER_3){
						RxState=8;
					}else{
						RxState=0;
					}
				}else if(RxState==8){
					if(radar_data == RECEIVE_FOOTER_4){
						RxState=0;
						radar_receive_ok_flag=1;
					}else{
						RxState=0;
					}
			}
			
			
			USART_ClearITPendingBit(UART5,USART_IT_RXNE);
		}
}

void right_radar_sendbyte(uint8_t Byte){
	while(!(USART_GetFlagStatus(UART5,USART_FLAG_TC) == 1));
	USART_SendData(UART5,Byte);
}

void right_radar_sendArray(const uint8_t *Array, uint16_t len)
{
		char *p = (char *)Array;
		
		while(len --){
			right_radar_sendbyte(*p);
			p ++;
		}
}

void right_radar_sendString(char *String)
{
	while(*String!='\0')
	{
		while(!(USART_GetFlagStatus(UART5,USART_FLAG_TC) == 1));
		USART_SendData(UART5,*String++);
	}
}

void right_radar_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	right_radar_sendString(String);
}