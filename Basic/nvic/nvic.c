#include "nvic.h"
#include "stm32f10x_exti.h"
#include "usart.h"
#include "inv_mpu.h"

u8 INT_MARK;//中断标志位
extern float acc[3],gyro[3],angle[3],quat[4];

void NVIC_INIT (void){	 
	NVIC_InitTypeDef  NVIC_InitStruct;
	EXTI_InitTypeDef  EXTI_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 	//启动GPIO时钟 （若更改Port需作修改）     
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);	//配置端口中断需要启用复用时钟

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  //默认使用PA0连接MPU6050的INT端口
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;  							//定义中断线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;             		//中断使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;  	  //中断模式为 中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;   //上升沿触发
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;  				//中断线     
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  				//使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级 0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;     	//子优先级   0
	NVIC_Init(& NVIC_InitStruct);

}

//若接收到INT端口高电平触发中断，则代表DMP数据更新了，需及时读取
//中断尽可能时间短 否则可能导致数据获取失败！
void  EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){//判断某个线上的中断是否发生 
		if(INT_MARK = mpu_dmp_get_data(angle,angle+1,angle+2,quat))
			printf("mpu_dmp_get_data Failed erorr num:%d\n\r",INT_MARK);	//若返回值为1则证明DMP获取数据失败
	}
//		INT_MARK=1;														//标志位置1
		EXTI_ClearITPendingBit(EXTI_Line0);   //清除 LINE 上的中断标志位
}     


