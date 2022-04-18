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

extern u8 USART1_Queue[SENDBUFF_SIZE];						//USARTx DMA���ͻ������
extern int FLASH_Queue[SENDBUFF_SIZE];					//�ڲ�FLASHд�뻺�����
extern float acc[3],gyro[3],angle[3],quat[4];				//���ٶȡ����ٶȡ��Ƕȡ���Ԫ��

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

void task1_task(void *pvParameters)
{
	u8 temp;
	TIMx_Init(60000,1200/50);						//��ʱ����ʼ��	
	
	if(MPU_Init())									//MPU6050��ʼ��
		printf("MPU��ʼ��ʧ�ܣ�����������\r\n");	  //����ֵΪ1���ʼ��ʧ��
	
    temp = mpu_dmp_init();                          //MPU6050 DMP���ܳ�ʼ�� ����ֵΪ1���ʼ��ʧ��
	while(temp){					
		printf("mpu_dmp erorr %d\r\n",temp);		//Ĭ���ϵ���ٶ�У׼����ˮƽ����
		Erorr_MPU();
	}

	NVIC_INIT();						//MPU6050��ʼ�������
	while(1)
	{
		LED_ON;
		vTaskDelay(50);
		LED_OFF;
		vTaskDelay(50);
	}
}
//�߳�2���������
void task2_task(void *pvParameters)
{
	while(1)
	{
		//		TIM_SetCompare1(TIM3,3000);
//		TIM_SetCompare2(TIM3,3000);
//		TIM_SetCompare3(TIM3,3000);
//		TIM_SetCompare4(TIM3,3000);
		Servo1_SetAngle;					//����դ����ƫת
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
