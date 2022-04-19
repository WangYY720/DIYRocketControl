#include "main.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE		128
TaskHandle_t	StartTask_Handle;
void start_task(void *pvParameters);

#define TASK1_TASK_PRIO		2
#define TASK1_STK_SIZE		128
TaskHandle_t	Task1Task_Handle;
void task1_task(void *pvParameters);

#define TASK2_TASK_PRIO		2
#define TASK2_STK_SIZE		128
TaskHandle_t	Task2Task_Handle;
void task2_task(void *pvParameters); 

#define TASK3_TASK_PRIO		2
#define TASK3_STK_SIZE		128
TaskHandle_t	Task3Task_Handle;
void task3_task(void *pvParameters);
	
u8 Is_Launch = 0;									//接收到发射信号标志位
u8 Is_SendData = 0,Is_Senddata_Again = 0;			//接收到传输数据标志位
u8 Is_FlashWrite = 0,Is_FlashRead = 0;				//接收读写flash标志位
u8 Is_ContactCheck;      							//接收到检查通讯状态标志位 									//接收到开伞信号标志位

// 开始任务
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
// 线程1：接收串口指令
void task1_task(void *pvParameters)
{
	//MPU6050陀螺仪初始化,开启I2C读取中断
	GYRO_Init();		

	LED_ON;
	BUZZER_BEEP_LONG1;
	printf("初始化完成！\r\n");

	while(1)
	{
		// 判断是否执行发射程序
		if(Is_Launch){
			Rocket_Launch();
		}
		// 判断是否执行发送飞行数据
		if(Is_SendData){
			Rocket_Senddata();
		}
		// 判断是否读取并发送flash数据
		if(Is_FlashRead){
			Rocket_Readflash();
		}
		// 判断是否检查通讯状态 
		if(Is_ContactCheck){
			Rocket_ContactCheck();
		}	
		// 延时
		vTaskDelay(1000/data_frequency);
	}
}
// 线程2：PID\驱动舵机
void task2_task(void *pvParameters)
{
	while(1)
	{
		// 执行姿态PID控制
		Rocket_PID();
		// 控制舵机
		Rocket_Servo();
		// 延时
		vTaskDelay(1000/PID_frequency);
	}
}
// 线程3：循环检查LED、蜂鸣器、点火、开伞是否需要触发
void task3_task(void *pvParameters)
{
	while(1)
	{
		// 检查点火、开伞是否需要执行
		FireTask();
		// 检查LED是否需要点亮、熄灭
		LEDTask();
		// 检查蜂鸣器是否需要触发、停止
		BuzzerTask();
		// 循环速率100Hz
		vTaskDelay(10);
	}
}
// 开始FreeRTOS调度
void StartRTOS(void)
{
	xTaskCreate((TaskFunction_t	)start_task,
							(const char*		)"start_task",
							(u16				)START_STK_SIZE,
							(void*				)NULL,
							(UBaseType_t		)START_TASK_PRIO,
							(TaskHandle_t		)&StartTask_Handle);
	vTaskStartScheduler();
}
