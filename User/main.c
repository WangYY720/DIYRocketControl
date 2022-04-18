/******************************************************
						դ�����STM32����ɿس���
******************************************************/
#include "main.h"
#include "usertask.h"

u8 USART1_Queue[SENDBUFF_SIZE]={0};					//USARTx DMA���ͻ������
int FLASH_Queue[SENDBUFF_SIZE]={0};					//�ڲ�FLASHд�뻺�����
float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��

int main(void)
{
    
    SystemInit(); 	 
	delay_init();	    							//��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//����ϵͳ�ж����ȼ�����4	

	delay_xms(500);
	USART_Config();								
	USART1_Init(9600);								//����1��ʼ��
	TIM_PWM_Init();									//�����ʼ��
	PID_Set_Goal(0,0,0);							//PID��ʼ��
	BuzzerLEDFire_Init();							//��������LED��ʼ��
	
	BUZZER_BEEP_SHORT2;
	
	USARTx_DMA_Config();				//��������1��DMA����
	delay_xms(500);
    
	StartRTOS();

}



