#include "internal_flash.h"   
#include "usart.h"

int Flash_Write_FloatBuffer(int *buffer,u16 num)
{
	uint32_t EraseCounter = 0x03; 	//��¼Ҫ��������ҳ
	uint32_t Address = 0x00;				//��¼д��ĵ�ַ
	uint32_t Data = 0x3210ABCD;			//��¼д�������
	uint32_t NbrOfPage = 0x00;			//��¼д�����ҳ
	
	FLASH_Status FLASHStatus = FLASH_COMPLETE; //��¼ÿ�β����Ľ��	

  /* ���� */
  FLASH_Unlock();

  /* ����Ҫ��������ҳ */
  NbrOfPage = num * 4 / FLASH_PAGE_SIZE + 1;

  /* ������б�־λ */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* ��ҳ����*/
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
  
	}
  
  /* ���ڲ�FLASHд������ */
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




