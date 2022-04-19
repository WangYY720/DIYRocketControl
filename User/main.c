/***************************************************************************
						栅格翼大创STM32火箭飞控程序
***************************************************************************/
#include "main.h"
#include "usertask.h"

int main(void)
{
    
    SystemInit(); 	 								// 系统初始化
	delay_init();	    							// 延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// 设置系统中断优先级分组4	

	delay_xms(500);
	USART_Config();									// 串口1初始化							
	USART1_Init(9600);								// 串口1初始化
	TIM_PWM_Init();									// 舵机初始化
	PID_Set_Goal(0,0,0);							// PID初始化
	BuzzerLED_Init();								// 蜂鸣器、LED初始化
	Fire_Init();									// 点火头、开伞初始化
	
	BUZZER_BEEP_SHORT2;								// 蜂鸣器提示
	
	USARTx_DMA_Config();							// 开启串口1的DMA功能
	delay_xms(500);
    
	StartRTOS();									// 开始RTOS调度

}



