#include "motor.h"


void MOTOR12_GPIO(void){
		GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOE时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    // 配置电机方向控制引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置速度
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;       // 上拉电阻
    GPIO_Init(GPIOE, &GPIO_InitStructure);              // 初始化GPIOE
	
		GPIO_ResetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
}


void MOTOR34_GPIO(void){
		GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOF时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // 配置电机方向控制引脚
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置速度
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;       // 上拉电阻
    GPIO_Init(GPIOF, &GPIO_InitStructure);              // 初始化GPIOF
	
		GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
}

// 初始化汽车控制系统
void Car_Init(void)
{
    MOTOR12_GPIO();
		MOTOR34_GPIO();
    PWM_init(); // 初始化PWM
		PWM_set_compare(0);
}

// 前进: 所有电机向前转动
void Car_Forward(void)
{
    // 设置电机1方向
    MOTOR1_DIR_PIN1=1;
    MOTOR1_DIR_PIN2=0;

    // 设置电机2方向
    MOTOR2_DIR_PIN1=1;
    MOTOR2_DIR_PIN2=0;

    // 设置电机3方向
    MOTOR3_DIR_PIN1=1;
    MOTOR3_DIR_PIN2=0;

    // 设置电机4方向
    MOTOR4_DIR_PIN1=1;
    MOTOR4_DIR_PIN2=0;
}

// 后退: 所有电机向后转动
void Car_Back(void)
{
    // 设置电机1方向
    MOTOR1_DIR_PIN1=0;
    MOTOR1_DIR_PIN2=1;

    // 设置电机2方向
    MOTOR2_DIR_PIN1=0;
    MOTOR2_DIR_PIN2=1;

    // 设置电机3方向
    MOTOR3_DIR_PIN1=0;
    MOTOR3_DIR_PIN2=1;

    // 设置电机4方向
    MOTOR4_DIR_PIN1=0;
    MOTOR4_DIR_PIN2=1;
}

// 左转: 左侧电机后退，右侧电机前进
void Car_Turn_Left(void)
{
    // 左侧电机反向
    MOTOR1_DIR_PIN1=0;
    MOTOR1_DIR_PIN2=1;
    MOTOR3_DIR_PIN1=0;
    MOTOR3_DIR_PIN2=1;

    // 右侧电机正向
    MOTOR2_DIR_PIN1=1;
    MOTOR2_DIR_PIN2=0;
    MOTOR4_DIR_PIN1=1;
    MOTOR4_DIR_PIN2=0;

}

// 右转: 右侧电机后退，左侧电机前进
void Car_Turn_Right(void)
{
    // 右侧电机反向
    MOTOR2_DIR_PIN1=0;
    MOTOR2_DIR_PIN2=1;
    MOTOR4_DIR_PIN1=0;
    MOTOR4_DIR_PIN2=1;

    // 左侧电机正向
    MOTOR1_DIR_PIN1=1;
    MOTOR1_DIR_PIN2=0;
    MOTOR3_DIR_PIN1=1;
    MOTOR3_DIR_PIN2=0;

}

// 停止: 所有电机停止
void Car_Stop(void)
{
    // 所有电机停止
    MOTOR2_DIR_PIN1=0;
    MOTOR2_DIR_PIN2=0;
    MOTOR4_DIR_PIN1=0;
    MOTOR4_DIR_PIN2=0;
    MOTOR1_DIR_PIN1=0;
    MOTOR1_DIR_PIN2=0;
    MOTOR3_DIR_PIN1=0;
    MOTOR3_DIR_PIN2=0;
}

// 设置速度: 修改PWM占空比
void Car_Set_Speed(uint16_t speed)
{
    PWM_set_compare(speed); // 设置PWM占空比为指定值
}
