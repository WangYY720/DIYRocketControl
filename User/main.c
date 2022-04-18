/******************************************************
						栅格翼大创STM32火箭飞控程序
******************************************************/
#include "main.h"
#include "usertask.h"

const u8 data_frequency = 50;						//PID更新及数传发送频率(TIMx中断频率)
u8 USART1_Queue[SENDBUFF_SIZE]={0};					//USARTx DMA发送缓存队列
int FLASH_Queue[SENDBUFF_SIZE]={0};					//内部FLASH写入缓存队列
float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数

int main(void)
{
	u8 temp;

    SystemInit(); 	 
	delay_init();	    							//延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//设置系统中断优先级分组4	

	delay_xms(500);
	USART_Config();								
	USART1_Init(9600);								//串口1初始化
	TIM_PWM_Init();									//舵机初始化
	PID_Set_Goal(0,0,0);							//PID初始化
	BuzzerLEDFire_Init();							//蜂鸣器、LED初始化
	
//	BUZZER_BEEP_SHORT2;
	
	// if(MPU_Init())									//MPU6050初始化
	// 	printf("MPU初始化失败！！！！！！\r\n");	  //返回值为1则初始化失败
	
    // temp = mpu_dmp_init();                          //MPU6050 DMP功能初始化 返回值为1则初始化失败
	// while(temp){					
	// 	printf("mpu_dmp erorr %d\r\n",temp);		//默认上电加速度校准，需水平放置
	// 	Erorr_MPU();
	// }
	
	USARTx_DMA_Config();				//开启串口1的DMA功能
	delay_xms(500);
	LED_ON;
//	BUZZER_BEEP_LONG1;
	printf("初始化完成！\r\n");
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//设置系统中断优先级分组4	
    
	StartRTOS();

    TIMx_Init(60000,1200/data_frequency);						//定时器初始化	
	NVIC_INIT();						//MPU6050开始输出数据
}



