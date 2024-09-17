#ifndef __MOTOR_H
#define __MOTOR_H	

#include "pwm.h"

#define MOTOR1_DIR_PIN1 GPIO_Pin_3  // 电机1方向控制引脚1
#define MOTOR1_DIR_PIN2 GPIO_Pin_4  // 电机1方向控制引脚2

#define MOTOR2_DIR_PIN1 GPIO_Pin_5  // 电机2方向控制引脚1
#define MOTOR2_DIR_PIN2 GPIO_Pin_6  // 电机2方向控制引脚2

#define MOTOR3_DIR_PIN1 GPIO_Pin_7  // 电机3方向控制引脚1
#define MOTOR3_DIR_PIN2 GPIO_Pin_8  // 电机3方向控制引脚2

#define MOTOR4_DIR_PIN1 GPIO_Pin_9  // 电机4方向控制引脚1
#define MOTOR4_DIR_PIN2 GPIO_Pin_10 // 电机4方向控制引脚2

void Car_Init(void);
void Car_Go_ForWard(void);
void Car_GO_Back(void);
void Car_Turn_Left(void);
void Car_Turn_Right(void);
void Car_Stop(void);
void Car_Set_Speed(uint16_t speed);

#endif

