/******************************************************
						栅格翼大创STM32火箭飞控程序
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "internal_flash.h"
#include "nvic.h"
#include "tim.h"
#include "mpu6050.h"
#include "buzzer.h"
#include "pid.h"
#include "servo.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};						//USARTx DMA发送缓存队列
int FLASH_Queue[SENDBUFF_SIZE]={0};					//内部FLASH写入缓存队列
const u8 data_frequency = 50;									//PID更新及数传发送频率(TIMx中断频率)
float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数
//u32 t=0,n=0;
extern u8 INT_MARK;														//NVIC中断标志位

int main(void)
{
	u8 temp=0;
	
	delay_init();
	Delay_ms(500);
	USART_Config();								
	USART1_Init(9600);						//串口1初始化
	TIM_PWM_Init();								//舵机初始化
	PID_Set_Goal(0,0,0);					//PID初始化
	BuzzerLEDFire_Init();							//蜂鸣器、LED初始化
	
	BUZZER_BEEP_SHORT2;
	
	if(MPU_Init())														//MPU6050初始化
		printf("MPU初始化失败！！！！！！\r\n");	//返回值为1则初始化失败

	while(temp = mpu_dmp_init()){							//MPU6050 DMP功能初始化 返回值为1则初始化失败
		printf("mpu_dmp erorr %d\r\n",temp);		//默认上电加速度校准，需水平放置
		while(1) BUZZER_BEEP_SHORT2;
	}
	
	USARTx_DMA_Config();											//开启串口1的DMA功能
	Delay_ms(1000);
	LED_ON;
	BUZZER_BEEP_LONG1;
	printf("初始化完成！\r\n");
	
	TIMx_Init(60000, 1200/data_frequency);		//中断TIM2初始化、计算公式：param1*param2*frequency = 72M	
	NVIC_INIT();															//MPU6050开始输出数据
	
	while(1){  
//		TIM_SetCompare1(TIM3,3000);
//		TIM_SetCompare2(TIM3,3000);
//		TIM_SetCompare3(TIM3,3000);
//		TIM_SetCompare4(TIM3,3000);
		Servo1_SetAngle;					//控制栅格翼偏转
		Servo2_SetAngle;
		Servo3_SetAngle;
		Servo4_SetAngle;
//		t++;
//		if(t==100000){
//			t=0;
//			if(n==0){
//				LED_OFF;
//				FIRE1_OFF;
//				FIRE2_OFF;
//				n=1;
//			}
//			else if(n==1){
//				LED_ON;
//				FIRE1_ON;
//				FIRE2_ON;
//				n=0;
//			}
//		}
		
	}
}



