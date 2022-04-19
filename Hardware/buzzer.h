#ifndef _BUZZER_H
#define _BUZZER_H

#include "stm32f10x.h"

// 是否允许蜂鸣器发声
#define BUZZER_ENABLE       0

#define BUZZER_GPIO			GPIOA
#define BUZZER_GPIO_Pin     GPIO_Pin_1

#define OFF                 0
#define ON                  1
#define SHORT1              2
#define SHORT2              3
#define LONG1               4
#define BLINK               10

#if BUZZER_ENABLE
#define BUZZER_SET          GPIO_SetBits(BUZZER_GPIO,BUZZER_GPIO_Pin)
#else
#define BUZZER_SET          ;
#endif
#define BUZZER_RESET        GPIO_ResetBits(BUZZER_GPIO,BUZZER_GPIO_Pin);
#define BUZZER_ON			BUZZER=ON
#define BUZZER_OFF			BUZZER=OFF
#define BUZZER_BEEP_SHORT1	BUZZER=SHORT1
#define BUZZER_BEEP_SHORT2	BUZZER=SHORT2
#define BUZZER_BEEP_LONG1	BUZZER=LONG1
#define BUZZER_BEEP_BLINK   BUZZER=BLINK

#define LED_GPIO			GPIOB
#define LED_GPIO_Pin		GPIO_Pin_5

#define LED_SET             GPIO_SetBits(LED_GPIO,LED_GPIO_Pin);
#define LED_RESET           GPIO_ResetBits(LED_GPIO,LED_GPIO_Pin);
#define LED_ON				LED=ON
#define LED_OFF				LED=OFF
#define LED_BLINK           LED=BLINK

#define FIRE1_GPIO			GPIOB
#define FIRE1_GPIO_Pin	    GPIO_Pin_13
#define FIRE2_GPIO			GPIOB
#define FIRE2_GPIO_Pin	    GPIO_Pin_12

extern u8 LED,BUZZER;

void BuzzerLED_Init(void);
void Buzzer_beep_short1(void);
void Buzzer_beep_long1(void);
void Buzzer_beep_short2(void);

void BuzzerTask(void);
void LEDTask(void);

#endif
