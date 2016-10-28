#include "uart.h"

void Uart_Init(short bound)
{
//	EA=1;//开总中断
//	
////	SCON=0x50;//设置工作方式为8位波特率可变
////	PCON=0x80;//波特率加倍
//	//TMOD=0x20;//定时器1工作模式8位自动重装
//	//TH1=TL1=256-(62500/bound);//溢出率=Sysclk/12/(256-TH1) 波特率=（2/32）x 溢出率
//	
//	ES=1;//开串口中断
//	//ET1=1;//开定时器中断
//	//TR1=1;//启动定时器
//	
//	
//	//STC12C单片机
//	//独立波特率发生器
//	BRT=256-(750000/bound);				   //溢出率=Sysclk/(256-BRT) 波特率=（2/32）x 溢出率	//12M 750000
//	SCON=0x50;//设置工作方式为8位波特率可变
//	PCON=0x80;//波特率加倍
//	AUXR=0x15;//使用独立波特兰发生器，每一个时钟计数一次


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

void Uart(void) interrupt 4
{
	uchar temp;
	if(RI==1)
	{	
		RI=0;
		temp=SBUF;
		UartSentChar(temp);
		//UartSendStr("test");
		
	}
}


void UartSentChar(uchar ch)
{
	SBUF=ch; //发送数据
	while(!TI);//等待发送完毕
	TI=0;
}

void UartSendStr(uchar *ch)
{
	while(*ch)
	{
		UartSentChar(*ch);
		ch++;
	}	
}

void Uart_SendNum(int num)		 //数字发送函数
{ 
  uchar ch[8] = {0};
  
  if(num < 0)
  {
    ch[0] = '-';
    num = -num;
  }
  else
    ch[0] = ' ';
  
  ch[1] = num / 100000 + '0';
  ch[2] = num % 100000 / 10000 + '0';
  ch[3] = num % 10000 /1000 + '0';
  ch[4]	= num % 1000 / 100 + '0';
  ch[5] = num % 100 / 10 + '0';
  ch[6]	= num % 10 + '0';

  UartSendStr(ch);
  UartSendStr("  ");
 //for(i=0;i<7;i++)
//	UartSendChar(ch[i]);
}

