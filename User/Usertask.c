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
	
u8 Is_Launch = 0;									//���յ������źű�־λ
u8 Is_SendData = 0,Is_Senddata_Again = 0;			//���յ��������ݱ�־λ
u8 Is_FlashWrite = 0,Is_FlashRead = 0;				//���ն�дflash��־λ
u8 Is_ContactCheck;      							//���յ����ͨѶ״̬��־λ 									//���յ���ɡ�źű�־λ

// ��ʼ����
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
// �߳�1�����մ���ָ��
void task1_task(void *pvParameters)
{
	//MPU6050�����ǳ�ʼ��,����I2C��ȡ�ж�
	GYRO_Init();		

	LED_ON;
	BUZZER_BEEP_LONG1;
	printf("��ʼ����ɣ�\r\n");

	while(1)
	{
		// �ж��Ƿ�ִ�з������
		if(Is_Launch){
			Rocket_Launch();
		}
		// �ж��Ƿ�ִ�з��ͷ�������
		if(Is_SendData){
			Rocket_Senddata();
		}
		// �ж��Ƿ��ȡ������flash����
		if(Is_FlashRead){
			Rocket_Readflash();
		}
		// �ж��Ƿ���ͨѶ״̬ 
		if(Is_ContactCheck){
			Rocket_ContactCheck();
		}	
		// ��ʱ
		vTaskDelay(1000/data_frequency);
	}
}
// �߳�2��PID\�������
void task2_task(void *pvParameters)
{
	while(1)
	{
		// ִ����̬PID����
		Rocket_PID();
		// ���ƶ��
		Rocket_Servo();
		// ��ʱ
		vTaskDelay(1000/PID_frequency);
	}
}
// �߳�3��ѭ�����LED������������𡢿�ɡ�Ƿ���Ҫ����
void task3_task(void *pvParameters)
{
	while(1)
	{
		// ����𡢿�ɡ�Ƿ���Ҫִ��
		FireTask();
		// ���LED�Ƿ���Ҫ������Ϩ��
		LEDTask();
		// ���������Ƿ���Ҫ������ֹͣ
		BuzzerTask();
		// ѭ������100Hz
		vTaskDelay(10);
	}
}
// ��ʼFreeRTOS����
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
