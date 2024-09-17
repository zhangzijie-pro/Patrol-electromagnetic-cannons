#include "motor.h"


void Car_Init(void)
{
	// 初始化方向GPIO
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOB时钟

  GPIO_InitStructure.GPIO_Pin = MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2 | 
																MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2 | 
																MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2 | 
																MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化

	PWM_initialize();
}

// 前进: 所有电机正转
void Car_Go_Forward(void)
{
    // 电机1正转
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN2);

    // 电机2正转
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN2);

    // 电机3正转
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN2);

    // 电机4正转
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // 电机1 PWM 50%
}

// 后退: 所有电机反转
void Car_Go_Back(void)
{
    // 电机1反转
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN2);

    // 电机2反转
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN2);

    // 电机3反转
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN2);

    // 电机4反转
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // 电机1 PWM 50%
}

// 左转: 左边电机反转，右边电机正转
void Car_Turn_Left(void)
{
    // 左边电机反转
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN2);

    // 右边电机正转
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN2);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN2);

    PWM_set_compare(50);  // 左边电机
}

// 右转: 右边电机反转，左边电机正转
void Car_Turn_Right(void)
{
    // 右边电机反转
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOB, MOTOR4_DIR_PIN2);

    // 左边电机正转
    GPIO_SetBits(GPIOB, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN2);
    GPIO_SetBits(GPIOB, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN2);

    PWM_set_compare(50);  // 左边电机
}

// 停止: 所有电机停止
void Car_Stop(void)
{
    // 所有电机停止
    GPIO_ResetBits(GPIOB, MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2);
    GPIO_ResetBits(GPIOB, MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2);

    // 设置PWM占空比为0，停止电机转动
    PWM_set_compare(0);
}


void Car_Set_Speed(uint16_t speed)
{
		PWM_set_compare(speed);
}
