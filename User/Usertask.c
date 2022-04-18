#include "main.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE		128
TaskHandle_t	StartTask_Handle;
void start_task(void *pvParameters);

#define TASK1_TASK_PRIO		3
#define TASK1_STK_SIZE		128
TaskHandle_t	Task1Task_Handle;
void task1_task(void *pvParameters);

#define TASK2_TASK_PRIO		2
#define TASK2_STK_SIZE		128
TaskHandle_t	Task2Task_Handle;
void task2_task(void *pvParameters); 

#define TASK3_TASK_PRIO		1
#define TASK3_STK_SIZE		128
TaskHandle_t	Task3Task_Handle;
void task3_task(void *pvParameters);

extern u8 USART1_Queue[SENDBUFF_SIZE];					//USARTx DMA发送缓存队列
extern int FLASH_Queue[SENDBUFF_SIZE];					//内部FLASH写入缓存队列
extern float acc[3],gyro[3],angle[3],quat[4];			//加速度、角速度、角度、四元数

u16 Queue_Pos = 0;		
u8 Is_Fire = 0;											//接收到发射信号标志位
u8 Is_SendData = 0,Is_Senddata_Again = 0;				//接收到传输数据标志位
u8 Is_FlashWrite = 0,Is_ReadFlash = 0;					//接收读写flash标志位
u8 Is_OpenFairing = 0;									//接收到开伞信号标志位
float fire_time=0;

void start_task(void *pvParameters)
{
	u8 flag;
	
	taskENTER_CRITICAL();
	
	flag = xTaskCreate((TaskFunction_t	)task1_task,
										(const char*		)"task1_task",
										(u16				)TASK1_STK_SIZE,
										(void*				)NULL,
										(UBaseType_t		)TASK1_TASK_PRIO,
										(TaskHandle_t		)&Task1Task_Handle);
	if(flag != pdPASS) Erorr_RTOS();
					
	flag = xTaskCreate((TaskFunction_t	)task2_task,
										(const char*		)"task2_task",
										(u16				)TASK2_STK_SIZE,
										(void*				)NULL,
										(UBaseType_t		)TASK2_TASK_PRIO,
										(TaskHandle_t		)&Task2Task_Handle);
	if(flag != pdPASS) Erorr_RTOS();
	
	flag = xTaskCreate((TaskFunction_t	)task3_task,
										(const char*		)"task3_task",
										(u16				)TASK3_STK_SIZE,
										(void*				)NULL,
										(UBaseType_t		)TASK3_TASK_PRIO,
										(TaskHandle_t		)&Task3Task_Handle);
	if(flag != pdPASS) Erorr_RTOS();								
										
	vTaskDelete(StartTask_Handle);
							
	taskEXIT_CRITICAL();
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
void task1_task(void *pvParameters)
{
	TIMx_Init(60000,1200/50);			//定时器初始化	
	GYRO_Init();						//MPU6050陀螺仪初始化,开启I2C读取中断

	LED_ON;
	BUZZER_BEEP_LONG1;
	printf("初始化完成！\r\n");

	while(1)
	{
		if(Is_Fire){
			if(fire_time < 0.001){
				printf("开始发射程序！\r\n");
				BUZZER_BEEP_LONG1;
			}
			if(fire_time <=TIME_Recode){
				USART1_Queue[Queue_Pos] 	= float2char(angle[0]);
				USART1_Queue[Queue_Pos+1] 	= float2char(angle[1]);
				USART1_Queue[Queue_Pos+2] 	= float2char(angle[2]);
				FLASH_Queue[Queue_Pos] 		= (int)(angle[0]*100.0);
				FLASH_Queue[Queue_Pos+1]	= (int)(angle[1]*100.0);
				FLASH_Queue[Queue_Pos+2]	= (int)(angle[2]*100.0);
				Queue_Pos += 3;
			}
			if(fire_time>TIME_Parachute && !Is_OpenFairing){
				BUZZER_BEEP_SHORT1;
				Is_OpenFairing = 1;
				printf("已经触发开伞 \r\n");
			}
			if(fire_time>TIME_Recode+1 && !Is_FlashWrite){
				Flash_Write_FloatBuffer(FLASH_Queue,SENDBUFF_SIZE);
				BUZZER_BEEP_SHORT1;
				Is_FlashWrite = 1;
				printf("已经将飞行数据写入FLASH \r\n");
			}
			fire_time += 1.0/(float)data_frequency;
			// printf("%.2f \n",fire_time);
			
		}

		if(Is_SendData){
			if(Is_Senddata_Again){
				USARTx_DMA_NOAMAL_RESTART();
				USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx ,DISABLE);
				DMA_ClearFlag(USART_TX_DMA_TCFLAG);
			}
			USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx ,ENABLE);
			BUZZER_BEEP_SHORT1;
			Is_Senddata_Again = 1;
			Is_SendData = 0;
		}
		
		if(Is_ReadFlash){
			Is_ReadFlash = 0;
			FLASH_Read_FloatBuffer(WRITE_START_ADDR,SENDBUFF_SIZE);
		}

		Pitch_angle = PID_Pitch(angle[0]);
		Roll_angle  = PID_Roll(angle[1]);

		vTaskDelay(1000/data_frequency);
	}
}
//线程2：驱动舵机
void task2_task(void *pvParameters)
{
	while(1)
	{
		//		TIM_SetCompare1(TIM3,3000);
//		TIM_SetCompare2(TIM3,3000);
//		TIM_SetCompare3(TIM3,3000);
//		TIM_SetCompare4(TIM3,3000);
		Servo1_SetAngle;					//控制栅格翼偏转
		Servo2_SetAngle;
		Servo3_SetAngle;
		Servo4_SetAngle;
//		t++;
//		if(t==100000){
//			t=0;
//			if(n==0){
//				LED_OFF;
//				FIRE1_OFF;
//				FIRE2_OFF;
//				n=1;
//			}
//			else if(n==1){
//				LED_ON;
//				FIRE1_ON;
//				FIRE2_ON;
//				n=0;
//			}
//		}
		vTaskDelay(50);
	}
}
void task3_task(void *pvParameters)
{
	while(1)
	{
		LED_ON;
		vTaskDelay(50);
		LED_OFF;
		vTaskDelay(50);
	}
}

void StartRTOS(void)
{
	xTaskCreate((TaskFunction_t	)start_task,
							(const char*		)"start_task",
							(u16						)START_STK_SIZE,
							(void*					)NULL,
							(UBaseType_t		)START_TASK_PRIO,
							(TaskHandle_t		)&StartTask_Handle);
	vTaskStartScheduler();
}
