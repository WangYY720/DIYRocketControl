#ifndef _SERVO_H
#define _SERVO_H

#include "stm32f10x.h"
#include "pwm.h"
#include "pid.h"

extern float acc[3],gyro[3],angle[3],quat[4];				//加速度、角速度、角度、四元数	
extern float Pitch_angle,Roll_angle,Yaw_angle;

//#define Servo1_SetAngle ServoSet(1,PID_Pitch(angle[0]))
#define Servo1_SetAngle ServoSet(1,Pitch_angle)
#define Servo2_SetAngle ServoSet(2,Roll_angle)
#define Servo3_SetAngle ServoSet(3,Pitch_angle)
#define Servo4_SetAngle ServoSet(4,Roll_angle)

//舵机转角设置函数
void ServoSet(u8 channel,float degree);


#endif

