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
	SPI_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
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
	SPI_FLASH_CS=0;                            //ʹ������   
    SPI_ReadWriteByte(0x02);      //����дҳ����   
    SPI_ReadWriteByte((uchar)((WriteAddr)>>16)); //����24bit��ַ    
    SPI_ReadWriteByte((uchar)((WriteAddr)>>8));   
    SPI_ReadWriteByte((uchar)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
		SPI_ReadWriteByte(pBuffer[i]);//ѭ��д��  

	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ 
	SPI_Flash_Wait_Busy();					   //�ȴ�д�����
} 

void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS=0;                            //ʹ������   
    SPI_ReadWriteByte(0x06);      //����дʹ��  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
} 

//�ȴ�����
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  

uchar SPI_Flash_ReadSR(void)   
{  
	uchar byte=0;   
	SPI_FLASH_CS=0;                            //ʹ������   
	SPI_ReadWriteByte(0x05);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     
	return byte;   
} 

void SPI_Flash_Read(uchar* pBuffer,uint ReadAddr,int NumByteToRead)   
{ 
 	int i;    												    
	SPI_FLASH_CS=0;                            //ʹ������   
    SPI_ReadWriteByte(0x03);         //���Ͷ�ȡ����   
    SPI_ReadWriteByte((uchar)((ReadAddr)>>16));  //����24bit��ַ    
    SPI_ReadWriteByte((uchar)((ReadAddr)>>8));   
    SPI_ReadWriteByte((uchar)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI_ReadWriteByte(0XFF);   //ѭ������  
    }
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
} 