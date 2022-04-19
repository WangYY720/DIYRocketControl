#include "fire.h"
#include "FreeRTOS.h"
#include "task.h"

u16 FIRE1=0,FIRE2=0;       // 发射和开伞触发标志位

void Fire_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	

    GPIO_InitStructure.GPIO_Pin   = FIRE1_Pin | FIRE2_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	
    GPIO_Init(FIRE_GPIO, &GPIO_InitStructure); 

    GPIO_ResetBits(FIRE_GPIO,FIRE1_Pin | FIRE2_Pin); 
}
void FireTask(void)
{
    switch(FIRE1){
        case OFF: FIRE1_RESET; break;
        case ON:  FIRE1_SET;   break;
        default:
            FIRE1_SET;
            vTaskDelay(FIRE1);
            FIRE1_RESET;
            FIRE1 = 0;
            break;
    }
    switch(FIRE2){
        case OFF: FIRE2_RESET; break;
        case ON:  FIRE2_SET;   break;
        default:
            FIRE2_SET;
            vTaskDelay(FIRE2);
            FIRE2_RESET;
            FIRE2 = 0;
            break;
    }
}

