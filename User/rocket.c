#include "main.h"

float MPU_Acceleration[3];      // 加速度
float MPU_AngularVelocity[3];   // 角速度
float MPU_Angle[3];             // 欧拉角
float MPU_Quat[4];			    // 四元数
float Servo_Angle[4];           // 4路舵机偏转角度	
float Launch_Time = 0;          // 发射后计时

float Pitch_angle,Roll_angle,Yaw_angle;         // 俯仰角、横滚角、偏航角

u8 USART1_Queue[SENDBUFF_SIZE];			        // USART1 DMA数据发送队列
int FLASH_Queue[SENDBUFF_SIZE];			        // FLASH 数据写入队列
u16 Queue_Pos;                                  // 队列位置标志位	
extern u8 Is_Launch;							// 接收到发射信号标志位
extern u8 Is_SendData,Is_Senddata_Again;		// 接收到发送数据标志位
extern u8 Is_FlashWrite,Is_FlashRead;			// 接收到读写FLASH标志位
extern u8 Is_ContactCheck;                      // 接收到串口通讯检查标志位   
u8 Is_Parachute = 0;                            // 开伞完成标志位

// 浮点型转整数函数，范围-128~128
u8 float2char(float Xfloat)
{
	if(Xfloat >= 128)
		return 255;
	else if(Xfloat <= -128)
		return 0;
	else return (int)Xfloat+128;
}

// 火箭发射处理函数
void Rocket_Launch(void)
{
    u8 temp;
    // 接收到发射信号，倒计时TIME_CountDowm秒
    if(Launch_Time < 0.001){
		printf("接收到发射信号！ \r\n");
        BUZZER_ON;
        LED_ON;
        for(temp = TIME_Countdown; temp>0; temp--){
            printf("发射倒计时 %d 秒！ \r\n",temp);
            vTaskDelay(1000);
        }
        FIRE1_SETms(500);
        BUZZER_OFF;
        LED_OFF;
        printf("火箭已经发射！ \r\n");
	}
    // 发射TIME_Recode内，保存欧拉角数据
	if(Launch_Time <= TIME_Recode){
		USART1_Queue[Queue_Pos] 	= float2char(MPU_Angle[0]);
		USART1_Queue[Queue_Pos+1] 	= float2char(MPU_Angle[1]);
		USART1_Queue[Queue_Pos+2] 	= float2char(MPU_Angle[2]);
		FLASH_Queue[Queue_Pos] 		= (int)(MPU_Angle[0]*100.0);
		FLASH_Queue[Queue_Pos+1]	= (int)(MPU_Angle[1]*100.0);
		FLASH_Queue[Queue_Pos+2]	= (int)(MPU_Angle[2]*100.0);
		Queue_Pos += 3;
	}
    // 发射TIME_Parachute秒后，触发开伞
	if(Launch_Time>TIME_Parachute && !Is_Parachute){
        FIRE2_SETms(200);
        BUZZER_BEEP_SHORT1;
		printf("已经触发开伞！ \r\n");
        Is_Parachute = 1;
	}
    // 发射TIME_Recode后，将欧拉角数据写入FLASH
	if(Launch_Time>TIME_Recode+1 && !Is_FlashWrite){
		Flash_Write_FloatBuffer(FLASH_Queue,SENDBUFF_SIZE);
		BUZZER_BEEP_SHORT1;
		printf("飞行数据已经写入FLASH！ \r\n");
        Is_FlashWrite = 1;
	}
    // 发射后计时,任务结束后闪灯提示
    if(Launch_Time < TIME_Recode+5){
	    Launch_Time += 1.0/(float)data_frequency;
    }else{
        BUZZER_BEEP_BLINK;
        LED_BLINK;
    }
}

// 串口传输u8保存格式飞行数据函数
void Rocket_Senddata(void)
{
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

// 读取并串口发送FLASH内浮点型飞行数据函数
void Rocket_Readflash(void)
{
    Is_FlashRead = 0;
	FLASH_Read_FloatBuffer(WRITE_START_ADDR,SENDBUFF_SIZE);
}

// PID处理函数
void Rocket_PID(void)
{
    // 姿态PID算法处理
    Pitch_angle = PID_Pitch(MPU_Angle[0]);
	Roll_angle  = PID_Roll(MPU_Angle[1]);
    // 设置舵机偏转角度
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
}

// 驱动舵机偏转函数
void Rocket_Servo(void)
{
    // 驱动舵机偏转置指定角度
    Servo1_SetAngle(Servo_Angle[0]);
	Servo2_SetAngle(Servo_Angle[1]);
	Servo3_SetAngle(Servo_Angle[2]);
	Servo4_SetAngle(Servo_Angle[3]);
}
// 串口通讯检查函数
void Rocket_ContactCheck(void)
{
    Is_ContactCheck = 0;
    BUZZER_BEEP_SHORT1;
    printf("串口通讯正常！ \r\n");
}
