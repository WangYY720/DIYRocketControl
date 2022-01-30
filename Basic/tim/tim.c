#include "tim.h"
#include "bsp_usart_dma.h"
#include "servo.h"
#include "buzzer.h"
#include "internal_flash.h"

#define FLASH_START_ADDR 0x0801f000

u8 flag=0;
extern u8 USART1_Queue[SENDBUFF_SIZE];
extern int FLASH_Queue[SENDBUFF_SIZE];
extern float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数
extern const u8 data_frequency;											//PID更新及数传发送频率(TIMx中断频率)
u16 Queue_Pos = 0;		//队列写入位置符
u8 Is_Fire = 0;				//接收到发射信号标志位
u8 Is_SendData = 0;		//接收到发射信号标志位
u8 Is_Senddata_Again = 0;
u8 Is_OpenFairing = 0 ,Is_FlashWrite = 0;
float fire_time=0;

void TIMx_Init(u16 arr,u16 psc){  														//TIM3 初始化 arr重装载值 psc预分频系数
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx,ENABLE);				//使能TIMx
    TIMx_NVIC_Init(); 																				//开启TIMx中断向量
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr-1; 									//设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc-1; 								//预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; 		//时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStrue); 						//TIMx初始化设置
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);								//使能TIMx中断    
    TIM_Cmd(TIMx,ENABLE); 																		//使能TIMx
}

void TIMx_NVIC_Init (void){ 																	//开启TIMx中断向量
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//设置抢占和子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

u8 float2char(float Xfloat)
{
//	u8 Xchar;
	if(Xfloat >= 128)
		return 255;
	else if(Xfloat <= -128)
		return 0;
	else return (int)Xfloat+128;
}

void TIMx_IRQHandler(void){ 																	//TIMx中断处理函数
	
	if (TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET){				//判断是否是TIMx中断
			TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
			
		if(Is_Fire){
			if(fire_time <= 12){
				USART1_Queue[Queue_Pos] 	= float2char(angle[0]);
				USART1_Queue[Queue_Pos+1] = float2char(angle[1]);
				USART1_Queue[Queue_Pos+2] = float2char(angle[2]);
				FLASH_Queue[Queue_Pos] 		= (int)(angle[0]*100.0);
				FLASH_Queue[Queue_Pos+1]	= (int)(angle[1]*100.0);
				FLASH_Queue[Queue_Pos+2]	= (int)(angle[2]*100.0);
				Queue_Pos += 3;
			}
			if(fire_time>5 && !Is_OpenFairing){
				BUZZER_BEEP_SHORT1;
				Is_OpenFairing = 1;
				printf("已触发开伞！\r\n");
			}
			if(fire_time>13 && !Is_FlashWrite){
				Flash_Write_FloatBuffer(FLASH_Queue,SENDBUFF_SIZE);
				BUZZER_BEEP_SHORT1;
				Is_FlashWrite = 1;
				printf("已将飞行数据写入FLASH！\r\n");
			}
			fire_time += 1.0/(float)data_frequency;
			
		}

		if(Is_SendData){
			if(Is_Senddata_Again){
				USARTx_DMA_NOAMAL_RESTART();
				USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx ,DISABLE);
				DMA_ClearFlag(USART_TX_DMA_TCFLAG);
			}
			USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx ,ENABLE);
			Is_Senddata_Again = 1;
			Is_SendData = 0;
		}
		
		Pitch_angle = PID_Pitch(angle[0]);
		Roll_angle  = PID_Roll(angle[1]);
		Servo1_SetAngle;
		Servo2_SetAngle;
		Servo3_SetAngle;
		Servo4_SetAngle;
		
	}	
} 


