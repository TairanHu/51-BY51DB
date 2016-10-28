#include "myspi.h"

uchar SPI_ReadWriteByte1(uchar dat) 		//mode3	  ����ģʽsck=1 CPOL=1 ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ CPHA=1
{
	uchar i,val=0;
	for(i=0;i<8;i++)
	{
		SPI_MOSI=0;
		if(dat&0x80)SPI_MOSI=1;//�������ݣ���λ��ǰ
		dat=dat<<1;
		SPI_CLK=0;//
		
		dat|=SPI_MISO;
		SPI_CLK=1;	
	}
	return dat;
}



uchar SPI_ReadWriteByte(uchar dat) 	 //mode0  ����ģʽsck=0 CPOL=0 ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ CPHA=0
{
	uchar i,val=0;
	for(i=0;i<8;i++)
	{
		SPI_MOSI=0;
		if(dat&0x80)SPI_MOSI=1;//�������ݣ���λ��ǰ
		dat=dat<<1;
		SPI_CLK=1;//
		
		dat|=SPI_MISO;
		SPI_CLK=0;	
	}
	return dat;
}