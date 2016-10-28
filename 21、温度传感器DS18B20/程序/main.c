/********************************************************

					DS18B20实验
				
				使用LCD1602显示当前温度						
			  
********************************************************/

#include <reg52.H>
#include <intrins.h>
#include "1602.h"
#include "DS18B20.h"


unsigned char  LedOut[5],LedNumVal;

void system_Ini()
{
    TMOD|= 0x11;
    TH1 = 0xD8;    //10
    TL1 = 0xF0;	
	IE = 0x8A;	
    TR1  = 1;
}

void main()
{ 

	system_Ini();		   // 系统初始化
	LcdInitiate();		   //  1602初始化

	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  
	WriteString("DS18B20 Test") ;
	WriteAddress(0x43);  
	WriteString("Tem:") ;

	while(1)
	{  	
	  GetTemp(); 		   //得到温度

	  LedOut[0]=Temperature%10000/1000+0x30;
      LedOut[1]=Temperature%1000/100+0x30;
      LedOut[2]=Temperature%100/10+0x30;	 //十位
      LedOut[3]=Temperature%10+0x30;    //个位
	  WriteAddress(0x48);  
	  WriteString(LedOut) ;		//显示温度
	  WriteString("C") ;
	}
}

