#ifndef FLASH_H
#define FLASH_H
#include "includes.h"

#define uchar unsigned char

uint SPI_Flash_ReadID(void);
void FLASH_Test(void);
void SPI_Flash_Write_Page(uchar* pBuffer,uint WriteAddr,int NumByteToWrite);
void SPI_FLASH_Write_Enable(void) ;
void SPI_Flash_Wait_Busy(void) ;
uchar SPI_Flash_ReadSR(void) ;
void SPI_Flash_Read(uchar* pBuffer,uint ReadAddr,int NumByteToRead)  ;







#endif
