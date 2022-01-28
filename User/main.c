/******************************************************
						դ�����STM32����ɿس���
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "nvic.h"
#include "tim.h"
#include "pwm.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "bsp_usart_dma.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};								//USARTx DMA���ͻ������
u16 frequency = 20;														//��������Ƶ��(TIMx�ж�Ƶ��)
float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��
short temp;																		

extern u8 INT_MARK;														//NVIC�жϱ�־λ

int main(void)
{
	u8 temp=0;
	
	RCC_Configuration();
	delay_init();
	delay_ms(500);
	USART_Config();
	TIM_PWM_Init();
	
	if(MPU_Init())													//MPU6050��ʼ��
		printf("MPU_Init Failed!\r\n");				//����ֵΪ1���ʼ��ʧ��
	while(temp = mpu_dmp_init())						//MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
		printf("mpu_dmp erorr :%d\r\n",temp);	//Ĭ���ϵ���ٶ�У׼����ˮƽ����
	
	delay_ms(100);
	USARTx_DMA_Config();
	TIMx_Init(60000, 1200/frequency);				//���㹫ʽ��param1*param2*frequency = 72M	
	NVIC_INIT();														//MPU6050��ʼ�������
	
	delay_ms(50);
	printf("��ʼ����������ѭ������\r\n");
	
	while(1){  
		
			ServoSet(1,angle[0]);
		
	}
}



