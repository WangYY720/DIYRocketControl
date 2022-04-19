#include "erorr.h"

#define DELAY	delay_xms(2000)

void LED_beep(u8 times)
{	
	u8 temp=0;
	for(;temp<times;temp++){
		LED_ON;
		delay_xms(150);
		LED_OFF;
		delay_xms(150);
	}
}

void Erorr_RTOS(void)
{
	while(1){
		BUZZER_ON;
		LED_beep(1);
		DELAY;
	}
}
void Erorr_MPU(void)
{
	while(1){
		BUZZER_ON;
		LED_beep(2);
		DELAY;
	}
}

