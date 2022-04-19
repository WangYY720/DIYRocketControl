#include "nvic.h"
#include "stm32f10x_exti.h"
#include "usart.h"
#include "inv_mpu.h"

extern float MPU_Acceleration[3];       //���ٶ�
extern float MPU_AngularVelocity[3];    //���ٶ�
extern float MPU_Angle[3];              //�Ƕ�
extern float MPU_Quat[4];				//��Ԫ��	

u8 INT_MARK;//�жϱ�־λ

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
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ� 0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;     	//�����ȼ�   0
	NVIC_Init(& NVIC_InitStruct);

}

//�����յ�INT�˿ڸߵ�ƽ�����жϣ������DMP���ݸ����ˣ��輰ʱ��ȡ
//�жϾ�����ʱ��� ������ܵ������ݻ�ȡʧ�ܣ�
void  EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){//�ж�ĳ�����ϵ��ж��Ƿ��� 
		if(mpu_dmp_get_data(MPU_Angle,MPU_Angle+1,MPU_Angle+2,MPU_Quat)){
			// printf("%f\n",angle);
			//printf("mpu_dmp_get_data Failed erorr num:%d\n\r",INT_MARK);
			}	//������ֵΪ1��֤��DMP��ȡ����ʧ��
//		mpu_dmp_get_data(angle,angle+1,angle+2,quat);
	
//		INT_MARK=1;														//��־λ��1
		EXTI_ClearITPendingBit(EXTI_Line0);   //��� LINE �ϵ��жϱ�־λ
	}
}     


