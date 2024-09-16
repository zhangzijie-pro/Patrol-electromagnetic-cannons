#ifndef __CONFIG_H
#define __CONFIG_H

#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_tim.h"

void deal_to_esp32_content(uint32_t *content);
void deal_esp32_return_content();

extern uint32_t esp32_return_data[6];

#endif