#ifndef _SERVO_H
#define _SERVO_H

#include "stm32f10x.h"
#include "pwm.h"
#include "pid.h"

extern float MPU_Acceleration[3];       //���ٶ�
extern float MPU_AngularVelocity[3];    //���ٶ�
extern float MPU_Angle[3];              //�Ƕ�
extern float MPU_Quat[4];				//��Ԫ��	
extern float Pitch_angle,Roll_angle,Yaw_angle;

//#define Servo1_SetAngle ServoSet(1,PID_Pitch(angle[0]))
#define Servo1_SetAngle(angle1) ServoSet(1,angle1)
#define Servo2_SetAngle(angle2) ServoSet(2,angle2)
#define Servo3_SetAngle(angle3) ServoSet(3,angle3)
#define Servo4_SetAngle(angle4) ServoSet(4,angle4)

//���ת�����ú���
void ServoSet(u8 channel,float degree);


#endif

