/******************************************************
						MPU6050调用固件库示例程序
						实验步骤详见readme.txt
******************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "mpu6050.h"
#include "inv_mpu.h"

u8 INT_MARK;//中断标志位
float acc[3],gyro[3],angle[3],quat[4];
short temp;
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
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     	//子优先级  2
	NVIC_Init(& NVIC_InitStruct);

}

//若接收到INT端口高电平触发中断，则代表DMP数据更新了，需及时读取
//中断尽可能时间短 否则可能导致数据获取失败！
void  EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){//判断某个线上的中断是否发生 
		if(INT_MARK = mpu_dmp_get_data(angle,angle+1,angle+2,quat))
			printf("mpu_dmp_get_data Failed erorr num:%d\n\r",INT_MARK);	//若返回值为1则证明DMP获取数据失败
//		else 
//			printf("欧拉角：%.2f %.2f %.2f\n\r",angle[0],angle[1],angle[2]);			//获取成功则将数据打印出来
//			printf("四元数：%.2f %.2f %.2f %.2f\n\r",quat[0],quat[1],quat[2],quat[3]);
		
		INT_MARK=1;														//标志位置1
		EXTI_ClearITPendingBit(EXTI_Line0);   //清除 LINE 上的中断标志位
	}     
}

int main(void)
{
	delay_init();
	delay_ms(500);
	USART1_Init(9600);
	if(MPU_Init())	//MPU6050初始化
		printf("MPU_Init Failed!\r\n");	//返回值为1则初始化失败
	else 
		printf("MPU_Init OK!\r\n");
	while(temp = mpu_dmp_init())			//MPU6050 DMP功能初始化 返回值为1则初始化失败
		printf("mpu_dmp_init Failed erorr num:%d\r\n",temp);	//默认上电加速度校准，需水平放置
	delay_ms(100);
	NVIC_INIT();	//MPU6050开始输出数据
	while(1){                                                             
			printf("欧拉角：%.2f %.2f %.2f\n\r",angle[0],angle[1],angle[2]);			//将数据打印出来
//			printf("四元数：%.2f %.2f %.2f %.2f\n\r",quat[0],quat[1],quat[2],quat[3]);
			
	};
}

