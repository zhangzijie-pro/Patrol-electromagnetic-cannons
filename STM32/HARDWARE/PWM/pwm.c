#include "pwm.h"

int PWM_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);                       //����TIM4��ʱ����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                     //����GPIOB��ʱ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);                     //PB6����ΪTIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);                     //PB7����ΪTIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);                     //PB8����ΪTIM4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);                     //PB9����ΪTIM4
	
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                              //ģʽ��Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                            //�����������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	//TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = 1680-1;                                 //����Ԥ��ƵֵPSC
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;               //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = 100-1;                                   //�Զ���װ��ֵ ARR
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                   //����ʱ�ӷָ� 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	 
  TIM_OCStructInit(&TIM_OCInitStructure); 																  //��ʼ���ṹ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                         //����ģʽΪPWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;             //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;     // CRR                                   //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                  //����ʱ����ֵС������ֵʱ������͵�ƽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	// ͨ��1
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);                         //ʹ��Ԥװ�ؼĴ���
 
  // ͨ��2 (PB7) PWM ��ʼ��
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// ͨ��3 (PB8) PWM ��ʼ��
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// ͨ��4 (PB9) PWM ��ʼ��
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
	TIM_ARRPreloadConfig(TIM4,ENABLE);                                        //ʹ��TIM4��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM4, ENABLE);                                                    //TIM4ʹ��
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);                                         //ʹ�������
	
	return 0;
}


void PWM_set_compare(int temp)
{
	TIM_SetCompare1(TIM4,temp);	                                              //�޸�ռ�ձ�
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);                       //����TIM4��ʱ����ʱ��
	
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
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);                                        //ʹ��TIM4��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM8, ENABLE);                                                    //TIM4ʹ��
	
	TIM_CtrlPWMOutputs(TIM8, ENABLE);                                         //ʹ�������
}


void PWM_set_compare_2(int value)
{
	TIM_SetCompare1(TIM8,value);
}

// Ƶ�� = CLK/ (PSC+1)/(ARR+1)
// ռ�ձ�=CCR/(ARR+1)
// �ֱ���=1/(ARR+1)

