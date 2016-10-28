#include "myspi.h"

uchar SPI_ReadWriteByte1(uchar dat) 		//mode3	  空闲模式sck=1 CPOL=1 数据采样从第二个时钟边沿开始 CPHA=1
{
	uchar i,val=0;
	for(i=0;i<8;i++)
	{
		SPI_MOSI=0;
		if(dat&0x80)SPI_MOSI=1;//发送数，高位在前
		dat=dat<<1;
		SPI_CLK=0;//
		
		dat|=SPI_MISO;
		SPI_CLK=1;	
	}
	return dat;
}



uchar SPI_ReadWriteByte(uchar dat) 	 //mode0  空闲模式sck=0 CPOL=0 数据采样从第一个时钟边沿开始 CPHA=0
{
	uchar i,val=0;
	for(i=0;i<8;i++)
	{
		SPI_MOSI=0;
		if(dat&0x80)SPI_MOSI=1;//发送数，高位在前
		dat=dat<<1;
		SPI_CLK=1;//
		
		dat|=SPI_MISO;
		SPI_CLK=0;	
	}
	return dat;
}