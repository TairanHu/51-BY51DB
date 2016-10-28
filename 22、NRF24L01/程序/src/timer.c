#include "timer.h"




void Timer0_Init(void)
{
	TMOD=0x01;
	EA=1;

	TH0=(65536-20000)/256;
	TL0=(65536-20000)%256;

	ET0=1;
	TR0=1;
}






void Timer0(void)interrupt 1
{
   	TH0=(65536-20000)/256;
	TL0=(65536-20000)%256;

	Timer0Count++;
	
}