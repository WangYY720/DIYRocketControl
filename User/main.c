/***************************************************************************
						դ�����STM32����ɿس���
***************************************************************************/
#include "main.h"
#include "usertask.h"

int main(void)
{
    
    SystemInit(); 	 								// ϵͳ��ʼ��
	delay_init();	    							// ��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// ����ϵͳ�ж����ȼ�����4	

	delay_xms(500);
	USART_Config();									// ����1��ʼ��							
	USART1_Init(9600);								// ����1��ʼ��
	TIM_PWM_Init();									// �����ʼ��
	PID_Set_Goal(0,0,0);							// PID��ʼ��
	BuzzerLED_Init();								// ��������LED��ʼ��
	Fire_Init();									// ���ͷ����ɡ��ʼ��
	
	BUZZER_BEEP_SHORT2;								// ��������ʾ
	
	USARTx_DMA_Config();							// ��������1��DMA����
	delay_xms(500);
    
	StartRTOS();									// ��ʼRTOS����

}



