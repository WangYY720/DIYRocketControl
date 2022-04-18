#include "tim.h"
#include "bsp_usart_dma.h"
#include "servo.h"
#include "buzzer.h"
#include "internal_flash.h"

#define FLASH_START_ADDR 0x0801f000

u8 flag=0;
extern u8 USART1_Queue[SENDBUFF_SIZE];
extern int FLASH_Queue[SENDBUFF_SIZE];
extern float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��


void TIMx_Init(u16 arr,u16 psc){  														//TIM3 ��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx,ENABLE);				//ʹ��TIMx
    TIMx_NVIC_Init(); 																				//����TIMx�ж�����
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr-1; 									//�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc-1; 								//Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; 		//ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStrue); 						//TIMx��ʼ������
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);								//ʹ��TIMx�ж�    
    TIM_Cmd(TIMx,ENABLE); 																		//ʹ��TIMx
}

void TIMx_NVIC_Init (void){ 																	//����TIMx�ж�����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x4;	//������ռ�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIMx_IRQHandler(void){ 																	//TIMx�жϴ�������
	
	if (TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET){				//�ж��Ƿ���TIMx�ж�
			TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
		
	}	
} 


