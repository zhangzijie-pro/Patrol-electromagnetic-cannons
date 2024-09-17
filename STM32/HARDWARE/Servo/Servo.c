#include "Servo.h"

void Servo_Init(void)
{
	PWM_init_2();
}

void Servo_Angle(float Angle){
	
	PWM_set_compare_2(Angle/180*2000+500);

}
