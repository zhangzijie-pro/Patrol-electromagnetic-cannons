#include "motor.h"
#include "hc04.h"

uint8_t HC_RxData;

// 初始化汽车控制系统
void Car_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOC时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // 配置电机方向控制引脚
    GPIO_InitStructure.GPIO_Pin = MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2 | 
                                   MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2 | 
                                   MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2 | 
                                   MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2;
    
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置速度
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉电阻
    GPIO_Init(GPIOF, &GPIO_InitStructure);              // 初始化GPIOF

    PWM_initialize(); // 初始化PWM
}

// 前进: 所有电机向前转动
void Car_Forward(void)
{
    // 设置电机1方向
    GPIO_SetBits(GPIOF, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR1_DIR_PIN2);

    // 设置电机2方向
    GPIO_SetBits(GPIOF, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR2_DIR_PIN2);

    // 设置电机3方向
    GPIO_SetBits(GPIOF, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR3_DIR_PIN2);

    // 设置电机4方向
    GPIO_SetBits(GPIOF, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR4_DIR_PIN2);

    PWM_set_compare(50); // 设置PWM占空比为50%
}

// 后退: 所有电机向后转动
void Car_Back(void)
{
    // 设置电机1方向
    GPIO_ResetBits(GPIOF, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR1_DIR_PIN2);

    // 设置电机2方向
    GPIO_ResetBits(GPIOF, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR2_DIR_PIN2);

    // 设置电机3方向
    GPIO_ResetBits(GPIOF, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR3_DIR_PIN2);

    // 设置电机4方向
    GPIO_ResetBits(GPIOF, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR4_DIR_PIN2);

    PWM_set_compare(50); // 设置PWM占空比为50%
}

// 左转: 左侧电机后退，右侧电机前进
void Car_Turn_Left(void)
{
    // 左侧电机反向
    GPIO_ResetBits(GPIOF, MOTOR1_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOF, MOTOR3_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR3_DIR_PIN2);

    // 右侧电机正向
    GPIO_SetBits(GPIOF, MOTOR2_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR2_DIR_PIN2);
    GPIO_SetBits(GPIOF, MOTOR4_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR4_DIR_PIN2);

    PWM_set_compare(50); // 设置PWM占空比为50%
}

// 右转: 右侧电机后退，左侧电机前进
void Car_Turn_Right(void)
{
    // 右侧电机反向
    GPIO_ResetBits(GPIOF, MOTOR2_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOF, MOTOR4_DIR_PIN1);
    GPIO_SetBits(GPIOF, MOTOR4_DIR_PIN2);

    // 左侧电机正向
    GPIO_SetBits(GPIOF, MOTOR1_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR1_DIR_PIN2);
    GPIO_SetBits(GPIOF, MOTOR3_DIR_PIN1);
    GPIO_ResetBits(GPIOF, MOTOR3_DIR_PIN2);

    PWM_set_compare(50); // 设置PWM占空比为50%
}

// 停止: 所有电机停止
void Car_Stop(void)
{
    // 所有电机停止
    GPIO_ResetBits(GPIOF, MOTOR1_DIR_PIN1 | MOTOR1_DIR_PIN2);
    GPIO_ResetBits(GPIOF, MOTOR2_DIR_PIN1 | MOTOR2_DIR_PIN2);
    GPIO_ResetBits(GPIOF, MOTOR3_DIR_PIN1 | MOTOR3_DIR_PIN2);
    GPIO_ResetBits(GPIOF, MOTOR4_DIR_PIN1 | MOTOR4_DIR_PIN2);

    // 设置PWM占空比为0，停止电机
    PWM_set_compare(0);
}

// 设置速度: 修改PWM占空比
void Car_Set_Speed(uint16_t speed)
{
    PWM_set_compare(speed); // 设置PWM占空比为指定值
}
