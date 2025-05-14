/*
 * flash.c
 *
 *  Created on: May 26, 2024
 *      Author: mzeu
 */

#include "flash.h"


#define FLASH_SECTOR_MAX      64

typedef struct
{
  uint32_t addr;
  uint32_t length;

} flash_tbl_t ;

static flash_tbl_t flash_tbl[FLASH_SECTOR_MAX];

static bool flashInSector(uint16_t sector_num,uint32_t addr, uint32_t length);

bool flashInit(void)
{
  for(int a=0;a<FLASH_SECTOR_MAX;a++)
  {
    flash_tbl[a].addr = 0x8000000 + a*1024;
    flash_tbl[a].length = 1024;
  }

  return true;
}
bool flashErase(uint32_t addr,uint32_t length)
{
  bool ret = false;
  HAL_StatusTypeDef  status;
  FLASH_EraseInitTypeDef Init;
  uint32_t page_error;

  int16_t start_sector_num = -1;
  uint32_t sector_count = 0;

  for(int aa=0;aa<FLASH_SECTOR_MAX;aa++)
  {
    if(flashInSector(aa,addr,length) == true)
    {
      if(start_sector_num < 0)
      {
        start_sector_num = aa ;
      }
      sector_count++;
    }
  }

  if(sector_count > 0)
  {
  HAL_FLASH_Unlock();
  Init.TypeErase   = FLASH_TYPEERASE_PAGES;
  Init.Banks       = FLASH_BANK_1;
  Init.PageAddress = flash_tbl[start_sector_num].addr;
  Init.NbPages     = sector_count;
  status =   HAL_FLASHEx_Erase(&Init, &page_error);

  if(status == HAL_OK)
  {
    ret = true;
  }
  HAL_FLASH_Lock();
  }

  return ret;
}
bool flashWrite(uint32_t addr,uint8_t *p_data,uint32_t length)
{
  bool ret = true;
  HAL_StatusTypeDef status;
  if(addr % 2 !=0)
  {
    return false;
  }

  HAL_FLASH_Unlock();

  for(int a=0;a<length;a+=2)
  {
    uint16_t data;

    data =  p_data[a+0] << 0;
    data |= p_data[a+1] << 8;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,  addr + a,(uint64_t)data);
    if(status != HAL_OK)
    {
      ret = false;
      break;
    }
  }
  HAL_FLASH_Lock();


  return ret;
}
bool flashRead(uint32_t addr,uint8_t *p_data,uint32_t length)
{
  bool ret= true;

  uint8_t *p_byte =(uint8_t *)addr;

  for(int a=0;a<length;a++)
  {
    p_data[a] = p_byte[a];
  }
  return ret;
}

bool flashInSector(uint16_t sector_num,uint32_t addr, uint32_t length)
{
  bool ret = false;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;

  sector_start =flash_tbl[sector_num].addr;
  sector_end =flash_tbl[sector_num].addr +flash_tbl[sector_num].length - 1;
  flash_start = addr;
  flash_end = addr + length - 1;

  if(sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = true;
  }

  if(sector_end >= flash_start && sector_end <=flash_end)
  {
    ret = true;
  }

  if(flash_start >=sector_start && flash_start <= sector_end)
  {
    ret = true;
  }
  if(flash_end >=sector_start && flash_end <= sector_end)
  {
    ret = true;
  }
  return ret;
}

