/********************************************************

					DS18B20ʵ��
				
				ʹ��LCD1602��ʾ��ǰ�¶�						
			  
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

	system_Ini();		   // ϵͳ��ʼ��
	LcdInitiate();		   //  1602��ʼ��

	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  
	WriteString("DS18B20 Test") ;
	WriteAddress(0x43);  
	WriteString("Tem:") ;

	while(1)
	{  	
	  GetTemp(); 		   //�õ��¶�

	  LedOut[0]=Temperature%10000/1000+0x30;
      LedOut[1]=Temperature%1000/100+0x30;
      LedOut[2]=Temperature%100/10+0x30;	 //ʮλ
      LedOut[3]=Temperature%10+0x30;    //��λ
	  WriteAddress(0x48);  
	  WriteString(LedOut) ;		//��ʾ�¶�
	  WriteString("C") ;
	}
}

