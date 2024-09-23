#include "Servo.h"

void Servo_Init(void)
{
	PWM_init_2();
}

void Servo_Angle(float Angle){
	
	uint32_t pulse = 1000 + (Angle * 1000 / 180);  // ���ݽǶȼ�������
	PWM_set_compare_2(pulse);
}
