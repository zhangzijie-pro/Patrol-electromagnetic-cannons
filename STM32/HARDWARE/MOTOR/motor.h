#ifndef __MOTOR_H
#define __MOTOR_H	

#include "pwm.h"

void Car_Init(void);
void Car_Go_ForWard(void);
void Car_GO_Back(void);
void Car_Turn_Left(void);
void Car_Turn_Right(void);
void Car_Stop(void);
void Car_Set_Speed(uint16_t speed);

#endif

