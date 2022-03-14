#ifndef _BUZZER_H
#define _BUZZER_H

#define BUZZER_GPIO			 		GPIOA
#define BUZZER_GPIO_Pin 		GPIO_Pin_1

#define BUZZER_ON						GPIO_SetBits(BUZZER_GPIO,BUZZER_GPIO_Pin)
#define BUZZER_OFF					GPIO_ResetBits(BUZZER_GPIO,BUZZER_GPIO_Pin)

#define BUZZER_BEEP_SHORT1	Buzzer_beep_short1();
#define BUZZER_BEEP_LONG1		Buzzer_beep_long1();
#define BUZZER_BEEP_SHORT2	Buzzer_beep_short2();

#define LED_GPIO				GPIOB
#define LED_GPIO_Pin		GPIO_Pin_5

#define LED_ON					GPIO_SetBits(LED_GPIO,LED_GPIO_Pin)
#define LED_OFF					GPIO_ResetBits(LED_GPIO,LED_GPIO_Pin)

#define FIRE1_GPIO			GPIOB
#define FIRE1_GPIO_Pin	GPIO_Pin_13
#define FIRE2_GPIO			GPIOB
#define FIRE2_GPIO_Pin	GPIO_Pin_12

#define FIRE1_ON				GPIO_SetBits(FIRE1_GPIO,FIRE1_GPIO_Pin)
#define FIRE1_OFF				GPIO_ResetBits(FIRE1_GPIO,FIRE1_GPIO_Pin)
#define FIRE2_ON				GPIO_SetBits(FIRE2_GPIO,FIRE2_GPIO_Pin)
#define FIRE2_OFF				GPIO_ResetBits(FIRE2_GPIO,FIRE2_GPIO_Pin)

void BuzzerLEDFire_Init(void);
void Buzzer_beep_short1(void);
void Buzzer_beep_long1(void);
void Buzzer_beep_short2(void);

#endif
