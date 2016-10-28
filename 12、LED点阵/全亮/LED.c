/********************************************************

					点阵实验
				
				LED点阵全亮						
	连接方法：P1口排针与8位数码管左边排针U11_JP1相连接
			  P0口排针与点阵右边排针LAH_R用排线相连接

********************************************************/


#include <reg52.h>

void main()
{
	while(1)
	{
		P0 = 0xff;		//LED正极全接到P0口，并置高
		P1 = 0x00;		//红色或绿色LED负极接到P1口，并置低
	}
}

