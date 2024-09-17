#ifndef __MOTOR_H
#define __MOTOR_H	

#include "pwm.h"

#define MOTOR1_DIR_PIN1 GPIO_Pin_3  // ���1�����������1
#define MOTOR1_DIR_PIN2 GPIO_Pin_4  // ���1�����������2

#define MOTOR2_DIR_PIN1 GPIO_Pin_5  // ���2�����������1
#define MOTOR2_DIR_PIN2 GPIO_Pin_6  // ���2�����������2

#define MOTOR3_DIR_PIN1 GPIO_Pin_7  // ���3�����������1
#define MOTOR3_DIR_PIN2 GPIO_Pin_8  // ���3�����������2

#define MOTOR4_DIR_PIN1 GPIO_Pin_9  // ���4�����������1
#define MOTOR4_DIR_PIN2 GPIO_Pin_10 // ���4�����������2

void Car_Init(void);
void Car_Forward(void);
void Car_Back(void);
void Car_Turn_Left(void);
void Car_Turn_Right(void);
void Car_Stop(void);
void Car_Set_Speed(uint16_t speed);

#endif

