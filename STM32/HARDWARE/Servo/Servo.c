#include "Servo.h"

void Servo_Init(void)
{
	PWM_init_2();
}

void Servo_Angle(float Angle){
	
	uint32_t pulse = (Angle/180*20)+5;  // ���ݽǶȼ�������
	PWM_set_compare_2(pulse);
}
