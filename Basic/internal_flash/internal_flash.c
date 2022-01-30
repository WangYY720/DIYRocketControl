#include "internal_flash.h"   
#include "usart.h"

int Flash_Write_FloatBuffer(int *buffer,u16 num)
{
	uint32_t EraseCounter = 0x03; 	//记录要擦除多少页
	uint32_t Address = 0x00;				//记录写入的地址
	uint32_t Data = 0x3210ABCD;			//记录写入的数据
	uint32_t NbrOfPage = 0x00;			//记录写入多少页
	
	FLASH_Status FLASHStatus = FLASH_COMPLETE; //记录每次擦除的结果	

  /* 解锁 */
  FLASH_Unlock();

  /* 计算要擦除多少页 */
  NbrOfPage = num * 4 / FLASH_PAGE_SIZE + 1;

  /* 清空所有标志位 */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* 按页擦除*/
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
  
	}
  
  /* 向内部FLASH写入数据 */
  Address = WRITE_START_ADDR;

  while((Address <= WRITE_START_ADDR+num*4) && (FLASHStatus == FLASH_COMPLETE))
  {
    FLASH_ProgramWord(Address,*buffer);
    Address = Address + 4;
		buffer = buffer + 1;
  }

  FLASH_Lock();
  
	return 0;
}

void FLASH_Read_FloatBuffer(u32 address,u16 num)
{
	u16 i;
	int output;
	for(i=1; i<=num; i+=1){
		output = *(u32*)(address);
		
		printf("%.2f ",(float)output/100.0);
//		output /= 100.0;
//		if(*(u32*)(address))
//			printf("%.2f ",output);
//		else 
//			printf("%.2f ",-output);
		
		if(i%3 == 0)
			printf("\r\n");
		
		address += 4;
		
	}
}




