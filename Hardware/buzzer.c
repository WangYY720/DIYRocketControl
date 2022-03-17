#include "buzzer.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

void Buzzer_Init(void)
{
	GPIO_InitTypeDef     GPIO_InitStrue;
	GPIO_InitStrue.GPIO_Pin=BUZZER_GPIO_Pin;     				
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;   	 	// ��������
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_2MHz;  	 //���õ�������ٶ�
  GPIO_Init(BUZZER_GPIO,&GPIO_InitStrue);        //GPIO�˿ڳ�ʼ������
	
	GPIO_ResetBits(BUZZER_GPIO,BUZZER_GPIO_Pin);
}
void Buzzer_beep_short1(void)
{
	BUZZER_ON;
	Delay_ms(500);
	BUZZER_OFF;
}
void Buzzer_beep_long1(void)
{
	BUZZER_ON;
	Delay_ms(1000);
	BUZZER_OFF;
}
void Buzzer_beep_short2(void)
{
	BUZZER_ON;
	Delay_ms(500);
	BUZZER_OFF;
	Delay_ms(200);
	BUZZER_ON;
	Delay_ms(500);
	BUZZER_OFF;
}
