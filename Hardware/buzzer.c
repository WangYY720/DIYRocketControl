#include "buzzer.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"

u8 LED=0, BUZZER=0;       // LED和蜂鸣器触发标志位

void BuzzerLED_Init(void)
{
	GPIO_InitTypeDef     GPIO_InitStrue;
	GPIO_InitStrue.GPIO_Pin=BUZZER_GPIO_Pin;     				
  	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;   	 	// 复用推挽
  	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_2MHz;  	 //设置低速输出速度
  	GPIO_Init(BUZZER_GPIO,&GPIO_InitStrue);        //GPIO端口初始化设置
	
	GPIO_ResetBits(BUZZER_GPIO,BUZZER_GPIO_Pin);
	
	GPIO_InitStrue.GPIO_Pin=LED_GPIO_Pin;     				
  	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;   	 	// 复用推挽
  	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_2MHz;  	 //设置低速输出速度
  	GPIO_Init(LED_GPIO,&GPIO_InitStrue);        //GPIO端口初始化设置
	
	GPIO_ResetBits(LED_GPIO,LED_GPIO_Pin);
	
}
void Buzzer_beep_short1(void)
{
	BUZZER_SET;
	delay_xms(200);
	BUZZER_RESET;
}
void Buzzer_beep_long1(void)
{
	BUZZER_SET;
	delay_xms(1000);
	BUZZER_RESET;
}
void Buzzer_beep_short2(void)
{
	BUZZER_SET;
	delay_xms(200);
	BUZZER_RESET;
	delay_xms(200);
	BUZZER_SET;
	delay_xms(200);
	BUZZER_RESET;
}
void Buzzer_beep_blink(void)
{
	BUZZER_SET;
	delay_xms(1000);
	BUZZER_RESET;
	delay_xms(1000);
}
void LED_blink(void)
{
	LED_SET;
	delay_xms(1000);
	LED_RESET;
	delay_xms(1000);
}
void BuzzerTask(void)
{
	switch(BUZZER)
	{
		case OFF	:	BUZZER_RESET; break;
		case ON		:	BUZZER_SET;   break;
		case SHORT1	:	Buzzer_beep_short1(); break;
		case SHORT2	:	Buzzer_beep_short2(); break;
		case LONG1	:	Buzzer_beep_long1();  break;
	}
}
void LEDTask(void)
{
	switch(LED)
	{
		case OFF	:	LED_RESET;	break;
		case ON		:	LED_SET;	break;
		case BLINK	:	LED_blink();break;
	}
}
