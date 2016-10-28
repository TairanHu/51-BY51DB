#include "flash.h"

void FLASH_Test(void)
{
	int temp;
	temp=SPI_Flash_ReadID();
	if(temp==W25Q64)
	{
		Show_f8x16str(0,0,"Flash Test Pass");
		
	}
	else   Show_f8x16str(0,0,"Flash Test Fail");
	Show_f8x16str(0,2,"MID:");
	Show_Num_f8x16(32,2,temp,5);

	
}

uint SPI_Flash_ReadID(void)
{
	uint Temp;	  
	SPI_FLASH_CS=0;				    
	SPI_ReadWriteByte(0x90);//∑¢ÀÕ∂¡»°ID√¸¡Ó	    
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 
	
	//SPI_ReadWriteByte(0xff); 			   
	Temp=SPI_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI_ReadWriteByte(0xFF);	 


	SPI_FLASH_CS=1;				    
	return Temp;
} 