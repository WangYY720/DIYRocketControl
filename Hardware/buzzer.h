#ifndef _BUZZER_H
#define _BUZZER_H

#define BUZZER_GPIO			 		GPIOA
#define BUZZER_GPIO_Pin 		GPIO_Pin_1

#define BUZZER_ON						GPIO_SetBits(BUZZER_GPIO,BUZZER_GPIO_Pin)
#define BUZZER_OFF					GPIO_ResetBits(BUZZER_GPIO,BUZZER_GPIO_Pin)

#define BUZZER_BEEP_SHORT1	Buzzer_beep_short1();
#define BUZZER_BEEP_LONG1		Buzzer_beep_long1();
#define BUZZER_BEEP_SHORT2	Buzzer_beep_short2();

void Buzzer_Init(void);
void Buzzer_beep_short1(void);
void Buzzer_beep_long1(void);
void Buzzer_beep_short2(void);

#endif
