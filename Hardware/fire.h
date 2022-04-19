#ifndef _FIRE_H
#define _FIRE_H

#include "stm32f10x.h"

#define ON  1
#define OFF 0

#define FIRE_GPIO       GPIOB
#define FIRE1_Pin       GPIO_Pin_13
#define FIRE2_Pin       GPIO_Pin_12

// 点火发射
#define FIRE1_SET       GPIO_SetBits(FIRE_GPIO,FIRE1_Pin)
#define FIRE1_RESET     GPIO_ResetBits(FIRE_GPIO,FIRE1_Pin)
#define FIRE1_ON        FIRE1=ON 
#define FIRE1_OFF       FIRE1=OFF
#define FIRE1_SETms(ms) FIRE1=ms
// 开伞
#define FIRE2_SET       GPIO_SetBits(FIRE_GPIO,FIRE2_Pin)
#define FIRE2_RESET     GPIO_ResetBits(FIRE_GPIO,FIRE2_Pin)
#define FIRE2_ON        FIRE2=ON 
#define FIRE2_OFF       FIRE2=OFF
#define FIRE2_SETms(ms) FIRE2=ms

extern u16 FIRE1,FIRE2;

void Fire_Init(void);
void FireTask(void);

#endif
