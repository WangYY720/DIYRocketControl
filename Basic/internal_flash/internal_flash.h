#ifndef __INTERNAL_FLASH_H
#define	__INTERNAL_FLASH_H

#include "stm32f10x.h"

/* STM32��������Ʒÿҳ��С2KByte���С�С������Ʒÿҳ��С1KByte */
#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)	//2048
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)	//1024
#endif

//д�����ʼ��ַ�������ַ
#define WRITE_START_ADDR  ((uint32_t)0x0800c000)
#define WRITE_END_ADDR    ((uint32_t)0x0801f000)

int Flash_Write_FloatBuffer(int *buffer,u16 num);
void FLASH_Read_FloatBuffer(u32 address,u16 num);


#endif /* __INTERNAL_FLASH_H */

