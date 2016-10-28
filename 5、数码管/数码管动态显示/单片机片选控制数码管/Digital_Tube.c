/**************************************************

 直接通过单片机控制数码管的位选，来选择哪一个数码管显示

 接线方法：单片机P0口接DIGJP，P1口接U11JP1


***************************************************/

#include <reg52.h>

#define uchar unsigned char

//此表为 LED 的字模, 共阴数码管 0-9  - 
uchar code Disp_Tab[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  - 
uchar code Disp_Bit[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdF, 0xbF, 0x7F};    //位选控制   查表的方法控制

/***********************************************

	   延时函数    延时时间大致为n毫秒

************************************************/
void delay_nms(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 110; j++) ;
	}	
}

/***********************************************

	  主函数

***********************************************/
void main()
{
	uchar Bit;               //定义变量位
	while(1)
	{		
		//从第一位数码管开始，逐个显示0-7
		for(Bit = 0; Bit < 8; Bit++)	  
		{
			P0 = Disp_Bit[Bit];
			P1 = Disp_Tab[Bit];
			delay_nms(1);
		}
	}
}

