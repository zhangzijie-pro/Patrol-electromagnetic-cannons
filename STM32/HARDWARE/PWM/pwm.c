#include "pwm.h"

int PWM_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);                       //开启TIM4定时器的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                     //开启GPIOB的时钟
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);                     //PB6复用为TIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);                     //PB7复用为TIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);                     //PB8复用为TIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);                     //PB9复用为TIM4
	
	//GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                              //模式设为复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                            //复用推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	//TIM4初始化
	TIM_TimeBaseStructure.TIM_Prescaler = 1680-1;                                 //设置预分频值PSC
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;               //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 100-1;                                   //自动重装载值 ARR
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                   //设置时钟分割 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	 
  TIM_OCStructInit(&TIM_OCInitStructure); 																  //初始化结构体
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                         //设置模式为PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;             //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;     // CRR                                   //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                  //当定时器的值小于脉冲值时，输出低电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	// 通道1
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);                         //使能预装载寄存器
 
  // 通道2 (PB7) PWM 初始化
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// 通道3 (PB8) PWM 初始化
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// 通道4 (PB9) PWM 初始化
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
	TIM_ARRPreloadConfig(TIM4,ENABLE);                                        //使能TIM4在ARR上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);                                                    //TIM4使能
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);                                         //使能主输出
	
	return 0;
}


void PWM_set_compare(int temp)
{
	TIM_SetCompare1(TIM4,temp);	                                              //修改占空比
	TIM_SetCompare2(TIM4,temp);
	TIM_SetCompare3(TIM4,temp);
	TIM_SetCompare4(TIM4,temp);
}

void PWM_init_2(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);                       //开启TIM4定时器的时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	TIM_TimBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseStruct.TIM_Period = 100-1;		// ARR
	TIM_TimBaseStruct.TIM_Prescaler = 1680-1;		// PSC
	TIM_TimBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8,&TIM_TimBaseStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState =  TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;		// CCR
	
	TIM_OC1Init(TIM8,&TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);                                        //使能TIM4在ARR上的预装载寄存器
	TIM_Cmd(TIM8, ENABLE);                                                    //TIM4使能
	
	TIM_CtrlPWMOutputs(TIM8, ENABLE);                                         //使能主输出
}


void PWM_set_compare_2(int value)
{
	TIM_SetCompare1(TIM8,value);
}

// 频率 = CLK/ (PSC+1)/(ARR+1)
// 占空比=CCR/(ARR+1)
// 分辨率=1/(ARR+1)

