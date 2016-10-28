#include "key.h"





uchar KeyScan(void)
{
	if(P0!=0xff)
	{
		Delay_ms(5);
		if(KEY1==0)
		return 1;

		else if(KEY2==0)
		return 2;

	}	

	return 0;
}