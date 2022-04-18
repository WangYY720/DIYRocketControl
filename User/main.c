/******************************************************
						栅格翼大创STM32火箭飞控程序
******************************************************/
#include "main.h"
#include "usertask.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};					//USARTx DMA发送缓存队列
int FLASH_Queue[SENDBUFF_SIZE]={0};					//内部FLASH写入缓存队列
float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数

int main(void)
{
    
    SystemInit(); 	 
	delay_init();	    							//延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//设置系统中断优先级分组4	

	delay_xms(500);
	USART_Config();								
	USART1_Init(9600);								//串口1初始化
	TIM_PWM_Init();									//舵机初始化
	PID_Set_Goal(0,0,0);							//PID初始化
	BuzzerLEDFire_Init();							//蜂鸣器、LED初始化
	
	BUZZER_BEEP_SHORT2;
	
	USARTx_DMA_Config();				//开启串口1的DMA功能
	delay_xms(500);
    
	StartRTOS();

}



