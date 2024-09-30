#include "Servo.h"

// C6  C7
void Servo_Init(void)
{
	PWM_init_servo();
}

void Servo_Angle_up(float Angle){
	
	uint32_t pulse = (Angle/180*20)+5;  // ���ݽǶȼ�������
	PWM_set_up(pulse);
}

void Servo_Angle_down(float Angle){
	
	uint32_t pulse = (Angle/180*20)+5;  // ���ݽǶȼ�������
	PWM_set_down(pulse);
}
