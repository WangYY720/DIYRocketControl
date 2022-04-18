/******************************************************
						դ�����STM32����ɿس���
******************************************************/
#include "main.h"
#include "usertask.h"

const u8 data_frequency = 50;						//PID���¼���������Ƶ��(TIMx�ж�Ƶ��)
u8 USART1_Queue[SENDBUFF_SIZE]={0};					//USARTx DMA���ͻ������
int FLASH_Queue[SENDBUFF_SIZE]={0};					//�ڲ�FLASHд�뻺�����
float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��

int main(void)
{
	u8 temp;

    SystemInit(); 	 
	delay_init();	    							//��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//����ϵͳ�ж����ȼ�����4	

	delay_xms(500);
	USART_Config();								
	USART1_Init(9600);								//����1��ʼ��
	TIM_PWM_Init();									//�����ʼ��
	PID_Set_Goal(0,0,0);							//PID��ʼ��
	BuzzerLEDFire_Init();							//��������LED��ʼ��
	
//	BUZZER_BEEP_SHORT2;
	
	// if(MPU_Init())									//MPU6050��ʼ��
	// 	printf("MPU��ʼ��ʧ�ܣ�����������\r\n");	  //����ֵΪ1���ʼ��ʧ��
	
    // temp = mpu_dmp_init();                          //MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
	// while(temp){					
	// 	printf("mpu_dmp erorr %d\r\n",temp);		//Ĭ���ϵ���ٶ�У׼����ˮƽ����
	// 	Erorr_MPU();
	// }
	
	USARTx_DMA_Config();				//��������1��DMA����
	delay_xms(500);
	LED_ON;
//	BUZZER_BEEP_LONG1;
	printf("��ʼ����ɣ�\r\n");
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//����ϵͳ�ж����ȼ�����4	
    
	StartRTOS();

    TIMx_Init(60000,1200/data_frequency);						//��ʱ����ʼ��	
	NVIC_INIT();						//MPU6050��ʼ�������
}



