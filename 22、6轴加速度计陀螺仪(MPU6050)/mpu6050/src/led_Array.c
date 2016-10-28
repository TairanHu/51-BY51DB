#include "led_array.h"

void LedArrat_test(void)
{
	uchar i;

	for(i=0;i<10;)
	{
		LedArray_ShowNum(i);
		if(Timer0Count==50)
		{
			Timer0Count=0;
			i++;
		}	
	}
	
}

void LedArray_ShowNum(uchar num)
{
	uchar i;

	for(i=0;i<8;i++)
	{
		LEDARRAY_DATA=ledarray_num[num][i];
		LEDARRAY_SCAN(i);
			
		Delay_ms(1);
		LEDARRAY_SCAN(8);
	}				
}

