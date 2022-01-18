/******************************************************
						MPU6050���ù̼���ʾ������
						ʵ�鲽�����readme.txt
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "mpu6050.h"
#include "inv_mpu.h"

u8 INT_MARK;//�жϱ�־λ
float acc[3],gyro[3],angle[3],quat[4];
short temp;
void NVIC_INIT (void){	 
	NVIC_InitTypeDef  NVIC_InitStruct;
	EXTI_InitTypeDef  EXTI_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 	//����GPIOʱ�� ��������Port�����޸ģ�     
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);	//���ö˿��ж���Ҫ���ø���ʱ��

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  //Ĭ��ʹ��PA0����MPU6050��INT�˿�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;  							//�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;             		//�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;  	  //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;   //�����ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;  				//�ж���     
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  				//ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     	//�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);

}

//�����յ�INT�˿ڸߵ�ƽ�����жϣ������DMP���ݸ����ˣ��輰ʱ��ȡ
//�жϾ�����ʱ��� ������ܵ������ݻ�ȡʧ�ܣ�
void  EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){//�ж�ĳ�����ϵ��ж��Ƿ��� 
		if(INT_MARK = mpu_dmp_get_data(angle,angle+1,angle+2,quat))
			printf("mpu_dmp_get_data Failed erorr num:%d\n\r",INT_MARK);	//������ֵΪ1��֤��DMP��ȡ����ʧ��
//		else 
//			printf("ŷ���ǣ�%.2f %.2f %.2f\n\r",angle[0],angle[1],angle[2]);			//��ȡ�ɹ������ݴ�ӡ����
//			printf("��Ԫ����%.2f %.2f %.2f %.2f\n\r",quat[0],quat[1],quat[2],quat[3]);
		
		INT_MARK=1;														//��־λ��1
		EXTI_ClearITPendingBit(EXTI_Line0);   //��� LINE �ϵ��жϱ�־λ
	}     
}

int main(void)
{
	delay_init();
	delay_ms(500);
	USART1_Init(9600);
	if(MPU_Init())	//MPU6050��ʼ��
		printf("MPU_Init Failed!\r\n");	//����ֵΪ1���ʼ��ʧ��
	else 
		printf("MPU_Init OK!\r\n");
	while(temp = mpu_dmp_init())			//MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
		printf("mpu_dmp_init Failed erorr num:%d\r\n",temp);	//Ĭ���ϵ���ٶ�У׼����ˮƽ����
	delay_ms(100);
	NVIC_INIT();	//MPU6050��ʼ�������
	while(1){                                                             
			printf("ŷ���ǣ�%.2f %.2f %.2f\n\r",angle[0],angle[1],angle[2]);			//�����ݴ�ӡ����
//			printf("��Ԫ����%.2f %.2f %.2f %.2f\n\r",quat[0],quat[1],quat[2],quat[3]);
			
	};
}

