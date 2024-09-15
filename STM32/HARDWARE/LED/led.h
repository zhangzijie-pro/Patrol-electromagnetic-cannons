#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED1 PFout(9)	  // D1
#define LED2 PFout(10)	// D2	 
#define LED1_OUT  GPIO_ResetBits(GPIOF,GPIO_Pin_9)
#define LED2_OUT  GPIO_ResetBits(GPIOF,GPIO_Pin_10)

void LED_Init(void);	 				    
#endif
