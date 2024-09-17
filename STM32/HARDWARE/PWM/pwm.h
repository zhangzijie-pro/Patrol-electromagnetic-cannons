#ifndef __pwm_h__
#define __pwm_h__
#include "sys.h"
#include "stm32f4xx.h"

int PWM_initialize(void);
void PWM_set_compare(int temp);

void PWM_init_2(void);
void PWM_set_compare_2(int value);

#endif
