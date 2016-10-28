/***************************************************
	
			串口接收发送数据实验
	电脑向单片机发送数据，单片机向电脑返回数据

****************************************************/

#include <reg52.h>

#define uchar unsigned char

uchar temp;		   //临时存储变量
uchar flag;        //串口中断标志位

void delay_nms(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}


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

void main()
{
	Serial_Port_Init();

	while(1)
	{
		if(flag)
		{
			SBUF = temp;			//SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
	        while(!TI);				// 等特数据传送	(TI发送中断标志)
			TI = 0;					// 清除数据传送标志		
			flag = 0;
		}

	}
	
}


void serail() interrupt 4
{
	RI = 0;				//清中断标志位
	temp = SBUF;		//接收到的数据存入temp
	flag = 1;			//flag标志位置1

}




