#include "pwm.h"

int PWM_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);                       //����TIM8��ʱ����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);                     //����GPIOI��ʱ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);                     //PI5����ΪTIM8
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                              //ģʽ��Ϊ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                            //�����������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	//TIM8��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;                                 //����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;               //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = 1680-1;                                   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                   //����ʱ�ӷָ� 
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);
	
	//TIM8 CH1 LED_RED 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                         //����ģʽΪPWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;             //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;           //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                                        //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                  //����ʱ����ֵС������ֵʱ������͵�ƽ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);                         //ʹ��Ԥװ�ؼĴ���
 
	TIM_ARRPreloadConfig(TIM8,ENABLE);                                        //ʹ��TIM8��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);                                                    //TIM8ʹ��
	
	TIM_CtrlPWMOutputs(TIM8, ENABLE);                                         //ʹ�������
	
	return 0;
}


int PWM_set_compare(int temp)
{
	TIM_SetCompare1(TIM8,temp);	                                              //�޸�ռ�ձ�
	return 0;
}

