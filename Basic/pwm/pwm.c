#include "pwm.h"


void TIM_PWM_Init(){  //TIM_PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    
		GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_PWM_TIMx,ENABLE);					//ʹ��TIMx�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ��GPIOAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//ʹ��GPIOBʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ��AFIOʱ��(��ʱ��3ͨ����ӳ��)
    
		GPIO_InitStrue.GPIO_Pin=PWM_Pin_1;     				// TIM_CH1
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    	// ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;   //�����������ٶ�
    GPIO_Init(PWM_GPIO_1,&GPIO_InitStrue);        //GPIO�˿ڳ�ʼ������
	
	  GPIO_InitStrue.GPIO_Pin=PWM_Pin_2;     				// TIM_CH2
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    	// ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz; 	//�����������ٶ�
    GPIO_Init(PWM_GPIO_2,&GPIO_InitStrue);        //GPIO�˿ڳ�ʼ������
	
	  GPIO_InitStrue.GPIO_Pin=PWM_Pin_3;     				// TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;   	// ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;   //�����������ٶ�
    GPIO_Init(PWM_GPIO_3,&GPIO_InitStrue);        //GPIO�˿ڳ�ʼ������
		
	  GPIO_InitStrue.GPIO_Pin=PWM_Pin_4;    				// TIM_CH4
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    	// ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;   //�����������ٶ�
    GPIO_Init(PWM_GPIO_4,&GPIO_InitStrue);        //GPIO�˿ڳ�ʼ������
    
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //ӳ�䣬��ӳ��ֻ����64��100��144�ŵ�Ƭ��
   //��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPA6��PA7,PB0,PB1
   //��������ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPB4��PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	      
    TIM_TimeBaseInitStrue.TIM_Period=PWMmax-1;   		 							 //�����Զ���װ��ֵ(60000��Ӧ20ms��1500-7500��Ӧpwm��)
    TIM_TimeBaseInitStrue.TIM_Prescaler=1440000/PWMmax-1;       	 //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;   	 //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;       	 //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(PWM_TIMx,&TIM_TimeBaseInitStrue);       				//TIMx��ʼ������(����PWM������)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        							// PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;							// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;					// ���ʹ��
		
		TIM_OC1Init(PWM_TIMx,&TIM_OCInitStrue);        									//TIMx��ͨ��1 PWM ģʽ����
		TIM_OC2Init(PWM_TIMx,&TIM_OCInitStrue);        									//TIMx��ͨ��2 PWM ģʽ����
		TIM_OC3Init(PWM_TIMx,&TIM_OCInitStrue);        									//TIMx��ͨ��3 PWM ģʽ����
    TIM_OC4Init(PWM_TIMx,&TIM_OCInitStrue);        									//TIMx��ͨ��4 PWM ģʽ����

    TIM_OCxPreloadConfig(PWM_TIMx,TIM_OCPreload_Enable);        		//ʹ��Ԥװ�ؼĴ���
    
    TIM_Cmd(PWM_TIMx,ENABLE);        																//ʹ��TIM3   
}




