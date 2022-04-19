#include "FreeRTOS.h"
#include "task.h"

extern u8 Is_Launch;							// 接收到发射信号标志位
extern u8 Is_SendData,Is_Senddata_Again;		// 接收到发送数据标志位
extern u8 Is_FlashWrite,Is_FlashRead;			// 接收到读写FLASH标志位
extern u8 Is_ContactCheck;                      // 接收到串口通讯检查标志位 

void StartRTOS(void);


