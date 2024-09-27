#ifndef __MOTOR_H
#define __MOTOR_H	

#include "pwm.h"

// GPIOF
#define MOTOR1_DIR_PIN1 PEout(0)
#define MOTOR1_DIR_PIN2 PEout(1)


#define MOTOR2_DIR_PIN1 PEout(2)
#define MOTOR2_DIR_PIN2 PEout(3)

#define MOTOR3_DIR_PIN1 PFout(0)
#define MOTOR3_DIR_PIN2 PFout(1)

#define MOTOR4_DIR_PIN1 PFout(2)
#define MOTOR4_DIR_PIN2 PFout(3)

void Car_Init(void);
void Car_Forward(void);
void Car_Back(void);
void Car_Turn_Left(void);
void Car_Turn_Right(void);
void Car_Stop(void);
void Car_Set_Speed(uint16_t speed);

#endif

