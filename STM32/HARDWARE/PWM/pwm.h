#ifndef __pwm_h__
#define __pwm_h__
#include "sys.h"
#include "stm32f4xx.h"

int PWM_initialize(void);
int PWM_set_compare(int temp);

#endif
