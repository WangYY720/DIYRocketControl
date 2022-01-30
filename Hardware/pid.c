#include "pid.h"

extern u8 data_frequency;
	
float GPitch,GRoll,GYaw;
float EPitch,ERoll,EYaw;
float IPitch,IRoll,IYaw;
float LPitch,LRoll,LYaw;
float DPitch,DRoll,DYaw;
float temp;

void PID_Init(void)
{
	Inte_Pitch = 0;
	Inte_Roll  = 0;
	Inte_Yaw	 = 0;
	Last_Pitch = 0;
	Last_Roll  = 0;
	Last_Yaw	 = 0;
}
void PID_Set_Goal(float pitch,float roll,float yaw)
{
	GPitch  = pitch;
	GRoll 	= roll;
	GYaw		= yaw;
//	PID_Init();
}
float PID_Pitch(float CurPitch)
{
	
	if(!Is_PID_Pitch) return 0;
		
	Erorr_Pitch = Goal_Pitch - CurPitch;
	Inte_Pitch += Erorr_Pitch * dt;
	if(Inte_Pitch > MaxI_Pitch){	
		Inte_Pitch = MaxI_Pitch;
	}
	else if(Inte_Pitch < -MaxI_Pitch){
		Inte_Pitch = - MaxI_Pitch;
	}
	Diff_Pitch 	= Last_Pitch - CurPitch;
	Last_Pitch	= CurPitch;
	
	temp = Kp*Erorr_Pitch + Ki*Inte_Pitch +Kd*Diff_Pitch;
	if(temp > Max_Pitch){	
		return Max_Pitch;
	}
	else if(temp < -Max_Pitch){
		return -Max_Pitch;
	}
	else return temp;
	
}
float PID_Roll(float CurRoll)
{
	
	if(!Is_PID_Roll) return 0;
	
	Erorr_Roll = Goal_Roll - CurRoll;
	Inte_Roll += Erorr_Roll * dt;
	if(Inte_Roll > MaxI_Roll){	
		Inte_Roll = MaxI_Roll;
	}
	else if(Inte_Roll < -MaxI_Roll){
		Inte_Roll = - MaxI_Roll;
	}
	Diff_Roll 	= Last_Roll - CurRoll;
	Last_Roll	= CurRoll;
	
	temp = Kp*Erorr_Roll + Ki*Inte_Roll +Kd*Diff_Roll;
	if(temp > Max_Roll){	
		return Max_Roll;
	}
	else if(temp < -Max_Roll){
		return -Max_Roll;
	}
	else return temp;
}
float PID_Yaw(float CurYaw)
{
	if(!Is_PID_Yaw) return 0;
	
	return 0;
}
