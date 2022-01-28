
#define  __PWM_H
#include "sys.h"

#define 	PWMmax	 		60000
#define 	PWM_TIMx		TIM3
#define 	RCC_PWM_TIMx		RCC_APB1Periph_TIM3
#define 	TIM_OCxPreloadConfig	TIM_OC3PreloadConfig

#define 	PWM_GPIO_1	GPIOA
#define 	PWM_Pin_1		GPIO_Pin_6
#define 	PWM_GPIO_2	GPIOA
#define 	PWM_Pin_2		GPIO_Pin_7
#define 	PWM_GPIO_3	GPIOB
#define 	PWM_Pin_3		GPIO_Pin_0
#define 	PWM_GPIO_4	GPIOB
#define 	PWM_Pin_4		GPIO_Pin_1

#define Servo1_SetAngle ServoSet(1,angle[0])
#define Servo2_SetAngle ServoSet(2,angle[1])
#define Servo3_SetAngle ServoSet(3,angle[0])
#define Servo4_SetAngle ServoSet(4,angle[1])

void TIM_PWM_Init();
//���ת�����ú���
void ServoSet(u8 channel,double degree);


