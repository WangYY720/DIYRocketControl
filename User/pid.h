#ifndef _PID_H
#define _PID_H

#include "stm32f10x.h"

#define Is_PID_Pitch	1
#define Is_PID_Roll		1
#define Is_PID_Yaw		0

extern float GPitch,GRoll,GYaw;
extern float EPitch,ERoll,EYaw;
extern float IPitch,IRoll,IYaw;
extern float LPitch,LRoll,LYaw;
extern float DPitch,DRoll,DYaw;

#define Goal_Pitch	    GPitch
#define Goal_Roll		GRoll
#define Goal_Yaw		GYaw
#define Erorr_Pitch	    EPitch
#define Erorr_Roll	    ERoll
#define Erorr_Yaw		EYaw
#define Inte_Pitch  	IPitch
#define Inte_Roll		IRoll
#define Inte_Yaw		IYaw
#define Last_Pitch	    LPitch
#define Last_Roll		LRoll
#define Last_Yaw	    LYaw
#define Diff_Pitch      DPitch
#define Diff_Roll	    DRoll
#define Diff_Yaw	    DYaw

#define MaxI_Pitch	    50
#define MaxI_Roll		50
#define MaxI_Yaw		50

#define Max_Pitch		30
#define Max_Roll		30
#define Max_Yaw			30

void PID_Init(void);
void PID_Set_Goal(float pitch,float roll,float yaw);
float PID_Pitch(float CurPitch);
float PID_Roll(float CurRoll);
float PID_Yaw(float CurYaw);

#endif
