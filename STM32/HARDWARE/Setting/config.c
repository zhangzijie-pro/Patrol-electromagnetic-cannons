#include "config.h"
#include "stm32f4xx_tim.h"

//* 解析报文 
//* 1.读取HC-04返回数据
//* 2.esp32-cam -> stm32f4: Usart		9字节报文 -> 5字节data

void deal_to_esp32_content(uint32_t *content)
{
	
}