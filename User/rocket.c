#include "main.h"

float MPU_Acceleration[3];      // ���ٶ�
float MPU_AngularVelocity[3];   // ���ٶ�
float MPU_Angle[3];             // ŷ����
float MPU_Quat[4];			    // ��Ԫ��
float Servo_Angle[4];           // 4·���ƫת�Ƕ�	
float Launch_Time = 0;          // ������ʱ

float Pitch_angle,Roll_angle,Yaw_angle;         // �����ǡ�����ǡ�ƫ����

u8 USART1_Queue[SENDBUFF_SIZE];			        // USART1 DMA���ݷ��Ͷ���
int FLASH_Queue[SENDBUFF_SIZE];			        // FLASH ����д�����
u16 Queue_Pos;                                  // ����λ�ñ�־λ	
extern u8 Is_Launch;							// ���յ������źű�־λ
extern u8 Is_SendData,Is_Senddata_Again;		// ���յ��������ݱ�־λ
extern u8 Is_FlashWrite,Is_FlashRead;			// ���յ���дFLASH��־λ
extern u8 Is_ContactCheck;                      // ���յ�����ͨѶ����־λ   
u8 Is_Parachute = 0;                            // ��ɡ��ɱ�־λ

// ������ת������������Χ-128~128
u8 float2char(float Xfloat)
{
	if(Xfloat >= 128)
		return 255;
	else if(Xfloat <= -128)
		return 0;
	else return (int)Xfloat+128;
}

// ������䴦����
void Rocket_Launch(void)
{
    u8 temp;
    // ���յ������źţ�����ʱTIME_CountDowm��
    if(Launch_Time < 0.001){
		printf("���յ������źţ� \r\n");
        BUZZER_ON;
        LED_ON;
        for(temp = TIME_Countdown; temp>0; temp--){
            printf("���䵹��ʱ %d �룡 \r\n",temp);
            vTaskDelay(1000);
        }
        FIRE1_SETms(500);
        BUZZER_OFF;
        LED_OFF;
        printf("����Ѿ����䣡 \r\n");
	}
    // ����TIME_Recode�ڣ�����ŷ��������
	if(Launch_Time <= TIME_Recode){
		USART1_Queue[Queue_Pos] 	= float2char(MPU_Angle[0]);
		USART1_Queue[Queue_Pos+1] 	= float2char(MPU_Angle[1]);
		USART1_Queue[Queue_Pos+2] 	= float2char(MPU_Angle[2]);
		FLASH_Queue[Queue_Pos] 		= (int)(MPU_Angle[0]*100.0);
		FLASH_Queue[Queue_Pos+1]	= (int)(MPU_Angle[1]*100.0);
		FLASH_Queue[Queue_Pos+2]	= (int)(MPU_Angle[2]*100.0);
		Queue_Pos += 3;
	}
    // ����TIME_Parachute��󣬴�����ɡ
	if(Launch_Time>TIME_Parachute && !Is_Parachute){
        FIRE2_SETms(200);
        BUZZER_BEEP_SHORT1;
		printf("�Ѿ�������ɡ�� \r\n");
        Is_Parachute = 1;
	}
    // ����TIME_Recode�󣬽�ŷ��������д��FLASH
	if(Launch_Time>TIME_Recode+1 && !Is_FlashWrite){
		Flash_Write_FloatBuffer(FLASH_Queue,SENDBUFF_SIZE);
		BUZZER_BEEP_SHORT1;
		printf("���������Ѿ�д��FLASH�� \r\n");
        Is_FlashWrite = 1;
	}
    // ������ʱ,���������������ʾ
    if(Launch_Time < TIME_Recode+5){
	    Launch_Time += 1.0/(float)data_frequency;
    }else{
        BUZZER_BEEP_BLINK;
        LED_BLINK;
    }
}

// ���ڴ���u8�����ʽ�������ݺ���
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

// ��ȡ�����ڷ���FLASH�ڸ����ͷ������ݺ���
void Rocket_Readflash(void)
{
    Is_FlashRead = 0;
	FLASH_Read_FloatBuffer(WRITE_START_ADDR,SENDBUFF_SIZE);
}

// PID������
void Rocket_PID(void)
{
    // ��̬PID�㷨����
    Pitch_angle = PID_Pitch(MPU_Angle[0]);
	Roll_angle  = PID_Roll(MPU_Angle[1]);
    // ���ö��ƫת�Ƕ�
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
    Servo_Angle[0] = 3*Pitch_angle;
}

// �������ƫת����
void Rocket_Servo(void)
{
    // �������ƫת��ָ���Ƕ�
    Servo1_SetAngle(Servo_Angle[0]);
	Servo2_SetAngle(Servo_Angle[1]);
	Servo3_SetAngle(Servo_Angle[2]);
	Servo4_SetAngle(Servo_Angle[3]);
}
// ����ͨѶ��麯��
void Rocket_ContactCheck(void)
{
    Is_ContactCheck = 0;
    BUZZER_BEEP_SHORT1;
    printf("����ͨѶ������ \r\n");
}
