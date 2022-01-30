/******************************************************
						栅格翼大创STM32火箭飞控程序
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "nvic.h"
#include "tim.h"
#include "mpu6050.h"
#include "buzzer.h"
#include "pid.h"
#include "servo.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};						//USARTx DMA发送缓存队列
const u8 data_frequency = 20;								//PID更新及数传发送频率(TIMx中断频率)
float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数

extern u8 INT_MARK;														//NVIC中断标志位

int main(void)
{
	u8 temp=0;
	
	RCC_Configuration();
	delay_init();
	Delay_ms(500);
	USART_Config();
	TIM_PWM_Init();
	Buzzer_Init();
	PID_Set_Goal(0,0,0);
	
	if(MPU_Init())													//MPU6050初始化
		printf("MPU_Init Failed!\r\n");				//返回值为1则初始化失败
	while(temp = mpu_dmp_init())						//MPU6050 DMP功能初始化 返回值为1则初始化失败
		printf("mpu_dmp erorr :%d\r\n",temp);	//默认上电加速度校准，需水平放置
	
	USARTx_DMA_Config();
	Delay_ms(1000);
	BUZZER_BEEP_SHORT2;
	TIMx_Init(60000, 1200/data_frequency);	//计算公式：param1*param2*frequency = 72M	
	NVIC_INIT();														//MPU6050开始输出数据
	
	while(1){  
		
		Servo1_SetAngle;
		Servo2_SetAngle;
		Servo3_SetAngle;
		Servo4_SetAngle;
		
	}
}



