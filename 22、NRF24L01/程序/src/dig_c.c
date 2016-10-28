#include "dig_c.h"

void DigC_Test(void)
{
	uchar i,j;

		for(i=0;i<8;i++)
		{
			DIG_C_SEL(i);
			DIG_C_DATA=F_DigC[i];
			Delay_ms(1);
			DIG_C_DATA=0x00;//ÏûÒþ
		}

	
//	DIG_C_SEL(0);
//	DIG_C_DATA=F_DigC[0];
//	Delay_ms(1);
//	DIG_C_SEL(1);
//	DIG_C_DATA=F_DigC[1];
//	Delay_ms(1);
	//DIG_C_SEL(2);
	////DIG_C_DATA=F_DigC[2];
	//Delay_ms(1);
	
	
}