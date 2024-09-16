#include "radar.h"

uint8_t enable_config_radar[] = {0xFD, 0xFC, 0xFB, 0xFA, 0x04, 0x00, 0xFF, 0x00, 0x01, 0x00, 0x04, 0x03, 0x02, 0x01};			// 使能配置
uint8_t disable_config_radar[] = {0xFD, 0xFC, 0xFB, 0xFA, 0x02, 0x00, 0xFE, 0x00, 0x04, 0x03, 0x02, 0x01};								// 结束配置

uint8_t radar_speed[] = {0xFD, 0xFC, 0xFB, 0xFA,0x08,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00, 0x04, 0x03, 0x02, 0x01, 0x04, 0x03, 0x02, 0x01};			// 雷达分辨率	6字节: [0:75cm距离门],[1:50cm距离门],[3:20cm距离门]
uint8_t read_speed[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x11,0x00, 0x04, 0x03, 0x02, 0x01};															// 读取雷达分辨率

uint8_t basic_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x07,0x00,0x02,0x00,0x01,0x0C,0x05,0x00,0x00, 0x04, 0x03, 0x02, 0x01};		// 基础设置	5字节: 一字节最小距离门,一字节最大距离门,两字节无人持续时间,1字节out输出0
uint8_t read_basic_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x12,0x00, 0x04, 0x03, 0x02, 0x01};												// 读取基础设置

uint8_t enable_work_model[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x62,0x00, 0x04, 0x03, 0x02, 0x01};												// 使能工作模式
uint8_t disable_work_model[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x63,0x00, 0x04, 0x03, 0x02, 0x01};											// 结束工作模式

uint8_t action_ling_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x10,0x00,0x03,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19, 0x04, 0x03, 0x02, 0x01};			// 运动灵敏度配置
uint8_t search_action_ling[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x13,0x00, 0x04, 0x03, 0x02, 0x01};											// 运动灵敏度查询

uint8_t static_ling_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x10,0x00,0x04,0x00,0x00,0x23,0x23,0x23,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19, 0x04, 0x03, 0x02, 0x01};			// 静止灵敏度配置
uint8_t search_static_ling[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x14,0x00, 0x04, 0x03, 0x02, 0x01};											// 静止灵敏度查询

uint8_t back[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x0B,0x00, 0x04, 0x03, 0x02, 0x01};																		// 动态背景校正
uint8_t search_back[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x1B,0x00, 0x04, 0x03, 0x02, 0x01};															// 动态背景校正进度查询

uint8_t read_hardware[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0xA0,0x00, 0x04, 0x03, 0x02, 0x01};														// 固件信息查询
uint8_t new_out[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0xA2,0x01,0x00,0x00, 0x04, 0x03, 0x02, 0x01};												// 恢复出厂
uint8_t restart[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0xA3,0x00, 0x04, 0x03, 0x02, 0x01};																	// 重启

uint8_t lanya[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0xA4,0x00,0x01,0x00, 0x04, 0x03, 0x02, 0x01};													// 蓝牙	0x01打开:0x00关闭

uint8_t light_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x04,0x00,0x0C,0x01,0x50, 0x04, 0x03, 0x02, 0x01};												// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值
uint8_t search_light_config[] = {0xFD, 0xFC, 0xFB, 0xFA,0x02,0x00,0x1C, 0x04, 0x03, 0x02, 0x01};													// 光感辅助控制 0x01: 0x00关闭,0x01小于阈值(0x0C:0x00~0xFF),0x02大于阈值


uint8_t radar_Serial_RxData;
uint8_t radar_Serial_RxFlag=0;

void radar_init(void)
{
	  // 1. 使能USART3和GPIOC时钟
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // 2. 配置PC10 (TX) 和 PC11 (RX) 为复用功能
		// 设置PC10为复用功能模式
    GPIOC->MODER &= ~(GPIO_MODER_MODER10);
    GPIOC->MODER |= (GPIO_MODER_MODER10_1); // 复用模式
    // 设置PC11为输入模式
    GPIOC->MODER &= ~(GPIO_MODER_MODER11);
    GPIOC->MODER |= (GPIO_MODER_MODER11);
    GPIOC->AFR[1] |= 0x0077; // 设置PC10和PC11为AF7（USART3）

    // 3. 配置USART3
    USART3->BRR = (uint16_t)(SystemCoreClock / 9600); // 波特率9600
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE; // 使能发送和接收
    USART3->CR1 |= USART_CR1_RXNEIE; // 使能接收中断
    USART3->CR1 |= USART_CR1_UE; // 使能USART3

    // 4. 使能USART3中断
    NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
}

void radar_IRQHandler(void){
	if(USART3->SR & USART_SR_RXNE){
		radar_Serial_RxData = USART3->DR;
		radar_Serial_RxFlag = 1;
	}
}

void radar_sendbyte(uint8_t Byte){
	while(!(USART3->SR&USART_SR_TXE));
	USART3->DR = Byte;
}

void radar_sendArray(uint8_t *Array, uint16_t len)
{
	for(uint16_t i=0;i<len;i++){
		radar_sendbyte(Array[i]);
	}
}

void radar_sendString(char *String)
{
	while(*String)
	{
		radar_sendbyte(*String++);
	}
}

uint32_t radar_pow(uint32_t x,uint32_t y)
{
	uint32_t result = 1;
	for(uint32_t i=0;i<y;i++){
		result*=x;
	}
	return result;
}

void radar_sendNumber(uint32_t Number, uint8_t len)
{
	for(int i=len;i>0;i--){
		uint8_t digit = (Number/radar_pow(10,i-1))%10;
		radar_sendbyte(digit+'0');
	}
}

int radar_fputc1(int ch, FILE *f)
{
	radar_sendbyte(ch);
	return ch;
}

void radar_prinf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	radar_sendString(String);
}

uint8_t radar_GetRxFlag(void)
{
	return radar_Serial_RxFlag;
}

uint8_t radar_GetRxData(void)
{
	radar_Serial_RxFlag = 0;
	return radar_Serial_RxData;
}
