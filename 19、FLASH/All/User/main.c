/********************************************************

						Flash实验
						
		将"Beyonday studio"写入芯片W25Q64的指定位置，
		同时从指定位置读取出来，并在OLED上面显示
		
********************************************************/


#include "includes.h"

uchar temp;

void Serial_Port_Init()
{
	TMOD = 0x20;	   // 设定T1定时器的工作方式2
	TH1 = 0xfd;		   // T1定时器装初值
	TL1 = 0xfd;		   //
	TR1 = 1;		   // 启动T1定时器
	SM0 = 0;		   // 设定串口工作方式1
	SM1 = 1;		   // 
	REN = 1;		   // 允许串口接收
	ES = 1;			   // 开串口中断
	EA = 1;			   // 开总中断

}

void main(void)
{

	uchar aaa[]="Beyonday studio";
	uchar bbb[18] = {0x00};
	uchar SIZE = sizeof(aaa);

	SPI_CLK=0;

	Serial_Port_Init();
	
	OLED_Init();

//	SPI_Flash_Write_Page(aaa,8*1024*1024-450,SIZE);
//	Delay_ms(1000);
	SPI_Flash_Read(bbb,8*1024*1024-450,SIZE)  ;
	Delay_ms(1000);
	Show_f8x16str(0,0,bbb);
	
	while(1)
	{
		
	}
}

void serail() interrupt 4
{
	RI = 0;				//清中断标志位
	temp = SBUF;		//接收到的数据存入temp
//	flag = 1;			//flag标志位置1

}


