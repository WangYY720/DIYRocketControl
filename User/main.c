/******************************************************
						栅格翼大创STM32火箭飞控程序
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "nvic.h"
#include "tim.h"
#include "pwm.h"
#include "mpu6050.h"
#include "buzzer.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};								//USARTx DMA发送缓存队列
u16 frequency = 20;														//数传发送频率(TIMx中断频率)
float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数		

extern u8 INT_MARK;														//NVIC中断标志位

int main(void)
{
	u8 temp=0;
	
	RCC_Configuration();
	delay_init();
	delay_ms(500);
	USART_Config();
	TIM_PWM_Init();
	Buzzer_Init();
	
	if(MPU_Init())													//MPU6050初始化
		printf("MPU_Init Failed!\r\n");				//返回值为1则初始化失败
	while(temp = mpu_dmp_init())						//MPU6050 DMP功能初始化 返回值为1则初始化失败
		printf("mpu_dmp erorr :%d\r\n",temp);	//默认上电加速度校准，需水平放置
	
	delay_ms(100);
	USARTx_DMA_Config();
	TIMx_Init(60000, 1200/frequency);				//计算公式：param1*param2*frequency = 72M	
	NVIC_INIT();														//MPU6050开始输出数据
	
	delay_ms(50);
	printf("初始化结束，主循环启动\r\n");
	BUZZER_BEEP_SHORT2;
	
	while(1){  
			
			Servo1_SetAngle;
		
	}
}



