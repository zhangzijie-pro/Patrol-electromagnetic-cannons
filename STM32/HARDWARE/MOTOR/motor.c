#include "motor.h"
#include "hc04.h"

uint8_t HC_RxData;

void Car_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2 | 
																MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2 | 
																MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2 | 
																MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

	PWM_initialize();
}

// ǰ��: ���е����ת
void Car_Forward(void)
{
    // ���1��ת
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN2);

    // ���2��ת
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN2);

    // ���3��ת
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN2);

    // ���4��ת
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // ���1 PWM 50%
}

// ����: ���е����ת
void Car_Back(void)
{
    // ���1��ת
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN2);

    // ���2��ת
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN2);

    // ���3��ת
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN2);

    // ���4��ת
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // ���1 PWM 50%
}

// ��ת: ��ߵ����ת���ұߵ����ת
void Car_Turn_Left(void)
{
    // ��ߵ����ת
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN2);

    // �ұߵ����ת
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN2);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // ��ߵ��
}

// ��ת: �ұߵ����ת����ߵ����ת
void Car_Turn_Right(void)
{
    // �ұߵ����ת
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN2);

    // ��ߵ����ת
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN2);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN2);

    PWM_set_compare(50);  // ��ߵ��
}

// ֹͣ: ���е��ֹͣ
void Car_Stop(void)
{
    // ���е��ֹͣ
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2);

    // ����PWMռ�ձ�Ϊ0��ֹͣ���ת��
    PWM_set_compare(0);
}


void Car_Set_Speed(uint16_t speed)
{
		PWM_set_compare(speed);
}

//void Control_hc_data(void){
//		HC_RxData = hc_GetRxData();
//		
//		// С����ʼ������50%��pwm
//		if(HC_RxData==0x0A){		// ǰ��
//			Car_Go_ForWard();
//		}
//		else if(HC_RxData==0x0B)	// ��ת
//		{
//			Car_Turn_Left();
//		}
//		else if(HC_RxData==0x0C)		// ��ת
//		{
//			Car_Turn_Right();
//		}
//		else if(HC_RxData==0x0D)		// ����
//		{
//			Car_GO_Back();
//		}
//		else if(HC_RxData==0x0E)		// ֹͣ
//		{
//			Car_Stop();
//		}
//}

