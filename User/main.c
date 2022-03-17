/******************************************************
						դ�����STM32����ɿس���
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

u8 USART1_Queue[SENDBUFF_SIZE]={0};						//USARTx DMA���ͻ������
int FLASH_Queue[SENDBUFF_SIZE]={0};					//�ڲ�FLASHд�뻺�����
const u8 data_frequency = 50;									//PID���¼���������Ƶ��(TIMx�ж�Ƶ��)
float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��
//u32 t=0,n=0;
extern u8 INT_MARK;														//NVIC�жϱ�־λ

int main(void)
{
	u8 temp=0;
	
	delay_init();
	Delay_ms(500);
	USART_Config();								
	USART1_Init(9600);						//����1��ʼ��
	TIM_PWM_Init();								//�����ʼ��
	PID_Set_Goal(0,0,0);					//PID��ʼ��
	BuzzerLEDFire_Init();							//��������LED��ʼ��
	
	BUZZER_BEEP_SHORT2;
	
	if(MPU_Init())														//MPU6050��ʼ��
		printf("MPU��ʼ��ʧ�ܣ�����������\r\n");	//����ֵΪ1���ʼ��ʧ��

	while(temp = mpu_dmp_init()){							//MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
		printf("mpu_dmp erorr %d\r\n",temp);		//Ĭ���ϵ���ٶ�У׼����ˮƽ����
		while(1) BUZZER_BEEP_SHORT2;
	}
	
	USARTx_DMA_Config();											//��������1��DMA����
	Delay_ms(1000);
	LED_ON;
	BUZZER_BEEP_LONG1;
	printf("��ʼ����ɣ�\r\n");
	
	TIMx_Init(60000, 1200/data_frequency);		//�ж�TIM2��ʼ�������㹫ʽ��param1*param2*frequency = 72M	
	NVIC_INIT();															//MPU6050��ʼ�������
	
	while(1){  
//		TIM_SetCompare1(TIM3,3000);
//		TIM_SetCompare2(TIM3,3000);
//		TIM_SetCompare3(TIM3,3000);
//		TIM_SetCompare4(TIM3,3000);
		Servo1_SetAngle;					//����դ����ƫת
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



