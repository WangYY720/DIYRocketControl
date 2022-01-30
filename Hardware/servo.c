#include "servo.h"

float Pitch_angle=0,Roll_angle=0,Yaw_angle=0;

void ServoSet(u8 channel,float degree)
{
	switch(channel){
		case 1:
			TIM_SetCompare1(PWM_TIMx,(int)((degree/90.0+1.5)*PWMmax/20.0));
			break;
		
		case 2:
			TIM_SetCompare2(PWM_TIMx,(int)((degree/90.0+1.5)*PWMmax/20.0));
			break;
		
		case 3:
			TIM_SetCompare3(PWM_TIMx,(int)((degree/90.0+1.5)*PWMmax/20.0));
			break;
		
		case 4:
			TIM_SetCompare4(PWM_TIMx,(int)((degree/90.0+1.5)*PWMmax/20.0));
			break;
		
	}
}

