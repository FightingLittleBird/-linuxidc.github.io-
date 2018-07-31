#include "flash.h"

/* Private variables ---------------------------------------------------------*/
uint32_t Address = 0;
uint32_t PageError = 0;
__IO uint32_t data32 = 0;
__IO uint32_t MemoryProgramStatus = 0;

/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;

/* Private function prototypes -----------------------------------------------*/

void flash_test()
{
    /* Unlock the Flash to enable the flash control register access *************/
    HAL_FLASH_Unlock();

    /* Erase the user Flash area
      (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
    EraseInitStruct.NbPages = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
    {
      /*
        Error occurred while page erase.
        User can add here some code to deal with this error.
        PageError will contain the faulty page and then to know the code error on this page,
        user can call function 'HAL_FLASH_GetError()'
      */
      /* Infinite loop */
      while (1)
      {

      }
    }

    /* Program the user Flash area word by word
      (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

    Address = FLASH_USER_START_ADDR;

    while (Address < FLASH_USER_END_ADDR)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, DATA_32) == HAL_OK)
      {
        Address = Address + 4;
      }
      else
      {
        /* Error occurred while writing data in Flash memory.
           User can add here some code to deal with this error */
        while (1)
        {

        }
      }
    }

    /* Lock the Flash to disable the flash control register access (recommended
       to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();

    /* Check if the programmed data is OK
        MemoryProgramStatus = 0: data programmed correctly
        MemoryProgramStatus != 0: number of words not programmed correctly ******/
    Address = FLASH_USER_START_ADDR;
    MemoryProgramStatus = 0x0;

    while (Address < FLASH_USER_END_ADDR)
    {
      data32 = *(__IO uint32_t *)Address;

      if (data32 != DATA_32)
      {
        MemoryProgramStatus++;
      }
      Address = Address + 4;
    }

    /*Check if there is an issue to program data*/
    if (MemoryProgramStatus == 0)
    {
      /* No error detected. Switch on LED2*/
      printf("data:%02X\r\n", data32);
    }
    else
    {
      /* Error detected. LED2 will blink with 1s period */
      while (1)
      {
      }
    }
}