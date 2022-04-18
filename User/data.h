#ifndef _DATA_H
#define _DATA_H

#include "stm32f10x.h"
#include "buzzer.h"
#include "delay.h"

// 开伞倒计时、数据记录时长(秒)					
#define TIME_Parachute	5
#define TIME_Recode		12
// 数据频率
#define data_frequency  40	
// 一次发送的数据量
#define SENDBUFF_SIZE   (3*TIME_Recode*data_frequency+1)   

#endif
