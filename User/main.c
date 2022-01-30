/******************************************************
						դ�����STM32����ɿس���
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

u8 USART1_Queue[SENDBUFF_SIZE]={0};						//USARTx DMA���ͻ������
const u8 data_frequency = 20;								//PID���¼���������Ƶ��(TIMx�ж�Ƶ��)
float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��

extern u8 INT_MARK;														//NVIC�жϱ�־λ

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
	
	if(MPU_Init())													//MPU6050��ʼ��
		printf("MPU_Init Failed!\r\n");				//����ֵΪ1���ʼ��ʧ��
	while(temp = mpu_dmp_init())						//MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
		printf("mpu_dmp erorr :%d\r\n",temp);	//Ĭ���ϵ���ٶ�У׼����ˮƽ����
	
	USARTx_DMA_Config();
	Delay_ms(1000);
	BUZZER_BEEP_SHORT2;
	TIMx_Init(60000, 1200/data_frequency);	//���㹫ʽ��param1*param2*frequency = 72M	
	NVIC_INIT();														//MPU6050��ʼ�������
	
	while(1){  
		
		Servo1_SetAngle;
		Servo2_SetAngle;
		Servo3_SetAngle;
		Servo4_SetAngle;
		
	}
}



