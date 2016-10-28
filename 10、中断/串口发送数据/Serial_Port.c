/***************************************************

		串口发送数据实验

		单片机向电脑发送数据

****************************************************/

#include <reg52.h>

#define uchar unsigned char

uchar code MESSAGE_TEST[] = " 百越创科工作室   UART Testing \n"; 

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
	int a = 0;
	Serial_Port_Init();

	while(1)
	{
		a = 0;
		while(MESSAGE_TEST[a] != '\0')
		{
			SBUF = MESSAGE_TEST[a];	//SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
	        while(!TI);				// 等特数据传送	(TI发送中断标志)
			TI = 0;					// 清除数据传送标志
						
			a++;					// 下一个字符
//			delay_nms(3);
			
		}
		delay_nms(1000);
	}
	
}

