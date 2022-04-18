#include "buzzer.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

void BuzzerLEDFire_Init(void)
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
	
	GPIO_InitStrue.GPIO_Pin=FIRE1_GPIO_Pin | FIRE2_GPIO_Pin;     				
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;   	 	// 复用推挽
  	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_2MHz;  	 //设置低速输出速度
  	GPIO_Init(FIRE1_GPIO,&GPIO_InitStrue);        //GPIO端口初始化设置
	
	GPIO_ResetBits(FIRE1_GPIO,FIRE1_GPIO_Pin | FIRE2_GPIO_Pin);
}
void Buzzer_beep_short1(void)
{
	BUZZER_ON;
	delay_xms(500);
	BUZZER_OFF;
}
void Buzzer_beep_long1(void)
{
	BUZZER_ON;
	delay_xms(1000);
	BUZZER_OFF;
}
void Buzzer_beep_short2(void)
{
	BUZZER_ON;
	delay_xms(500);
	BUZZER_OFF;
	delay_xms(200);
	BUZZER_ON;
	delay_xms(500);
	BUZZER_OFF;
}
