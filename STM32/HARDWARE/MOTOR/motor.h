#ifndef __MOTOR_H
#define __MOTOR_H	

#include "pwm.h"

#define MOTOR1_DIR_PIN1 GPIO_Pin_3 
#define MOTOR1_DIR_PIN2 GPIO_Pin_4 

#define MOTOR2_DIR_PIN1 GPIO_Pin_5
#define MOTOR2_DIR_PIN2 GPIO_Pin_6

#define MOTOR3_DIR_PIN1 GPIO_Pin_7
#define MOTOR3_DIR_PIN2 GPIO_Pin_8

#define MOTOR4_DIR_PIN1 GPIO_Pin_9
#define MOTOR4_DIR_PIN2 GPIO_Pin_10

void Car_Init(void);
void Car_Forward(void);
void Car_Back(void);
void Car_Turn_Left(void);
void Car_Turn_Right(void);
void Car_Stop(void);
void Car_Set_Speed(uint16_t speed);

#endif

