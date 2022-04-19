#ifndef _ROCKET_H
#define _ROCKET_H

// 发射倒计时、开伞倒计时、数据记录时长(秒)	
#define TIME_Countdown  5				
#define TIME_Parachute	5
#define TIME_Recode		12
// 数据频率
#define data_frequency  40
// PID频率
#define PID_frequency   50 	
// 一次发送的数据量
#define SENDBUFF_SIZE   (3*TIME_Recode*data_frequency+1) 

void Rocket_Launch(void);
void Rocket_Senddata(void);
void Rocket_Readflash(void);
void Rocket_PID(void);
void Rocket_Servo(void);
void Rocket_ContactCheck(void);

#endif

