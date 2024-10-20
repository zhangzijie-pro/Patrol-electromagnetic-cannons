#include "shoot.h"

void recharge_init(){
	RCC_AHB1PeriphClockCmd(RCC_SHOOT,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin = SHOOT_PIN | RECHARGE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(SHOOT, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(SHOOT,SHOOT_PIN | RECHARGE_PIN);
}
