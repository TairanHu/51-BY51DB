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
	SPI_ReadWriteByte(0x90);//发送读取ID命令	    
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 
	
	//SPI_ReadWriteByte(0xff); 			   
	Temp=SPI_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI_ReadWriteByte(0xFF);	 


	SPI_FLASH_CS=1;				    
	return Temp;
} 

void SPI_Flash_Write_Page(uchar* pBuffer,uint WriteAddr,int NumByteToWrite)
{
 	int i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS=0;                            //使能器件   
    SPI_ReadWriteByte(0x02);      //发送写页命令   
    SPI_ReadWriteByte((uchar)((WriteAddr)>>16)); //发送24bit地址    
    SPI_ReadWriteByte((uchar)((WriteAddr)>>8));   
    SPI_ReadWriteByte((uchar)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
		SPI_ReadWriteByte(pBuffer[i]);//循环写数  

	SPI_FLASH_CS=1;                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 

void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS=0;                            //使能器件   
    SPI_ReadWriteByte(0x06);      //发送写使能  
	SPI_FLASH_CS=1;                            //取消片选     	      
} 

//等待空闲
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  

uchar SPI_Flash_ReadSR(void)   
{  
	uchar byte=0;   
	SPI_FLASH_CS=0;                            //使能器件   
	SPI_ReadWriteByte(0x05);    //发送读取状态寄存器命令    
	byte=SPI_ReadWriteByte(0Xff);             //读取一个字节  
	SPI_FLASH_CS=1;                            //取消片选     
	return byte;   
} 

void SPI_Flash_Read(uchar* pBuffer,uint ReadAddr,int NumByteToRead)   
{ 
 	int i;    												    
	SPI_FLASH_CS=0;                            //使能器件   
    SPI_ReadWriteByte(0x03);         //发送读取命令   
    SPI_ReadWriteByte((uchar)((ReadAddr)>>16));  //发送24bit地址    
    SPI_ReadWriteByte((uchar)((ReadAddr)>>8));   
    SPI_ReadWriteByte((uchar)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI_ReadWriteByte(0XFF);   //循环读数  
    }
	SPI_FLASH_CS=1;                            //取消片选     	      
} 