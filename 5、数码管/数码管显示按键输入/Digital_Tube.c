/**************************************************

 按键调节数码管数字显示
 独立键盘上面四个分别加1,10,100,1000
 下面四个则是减

 接线方法：单片机P0口接DIGJP，P1口接U11JP1


***************************************************/

#include <reg52.h>

#define uchar unsigned char

//此表为 LED 的字模, 共阴数码管 0-9  - 
uchar code Disp_Tab[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  - 
uchar code Disp_Bit[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdF, 0xbF, 0x7F};    //位选控制   查表的方法控制

uchar LED_Out[8] = {0x00};
uchar KeyPort;

void display();

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
//	uchar Bit;               //定义变量位

	int Num_High , Num_Low;	 //定义数字的高四位和低四位
	
	Num_High = 0;
	Num_Low = 0;

	while(1)
	{
		

		if(Num_Low >= 10000)
		{
			Num_High++;
			Num_Low %= 1000;
		}

		LED_Out[0] = Num_Low%10;		//取出数字个位
		LED_Out[1] = Num_Low/10%10;     //取出数字十位
		LED_Out[2] = Num_Low/100%10;    //取出数字百位
		LED_Out[3] = Num_Low/1000%10;   //取出数字千位
                                        
		LED_Out[4] = Num_High%10;       //取出数字万位
		LED_Out[5] = Num_High/10%10;    //取出数字十万位
		LED_Out[6] = Num_High/100%10;   //取出数字百万位
		LED_Out[7] = Num_High/1000%10;  //取出数字千万位

		KeyPort = P2;
		
		while(P2 != 0xff)
		{
			display();
		}		

		switch(KeyPort)		//检测是哪个按键被按下
		{
			case 0xfe: Num_Low += 1;    break;
			case 0xfd: Num_Low += 10;   break;
			case 0xfb: Num_Low += 100;  break;
			case 0xf7: Num_Low += 1000; break;
			
			case 0xef: Num_Low -= 1;    break;
			case 0xdf: Num_Low -= 10;   break;
			case 0xbf: Num_Low -= 100;  break;
			case 0x7f: Num_Low -= 1000; break; 
		}
		
		display();		
//		//从第一位数码管开始，逐个显示
//		for(Bit = 0; Bit < 8; Bit++)	  
//		{
//			P0 = Disp_Bit[Bit];
//			P1 = Disp_Tab[LED_Out[8-Bit]];
//			delay_nms(1);
//		}
	}
}


void display()
{
	uchar Bit;               //定义变量位

	//从第一位数码管开始，逐个显示
	for(Bit = 0; Bit < 8; Bit++)	  
	{
		P0 = Disp_Bit[Bit];
		P1 = Disp_Tab[LED_Out[7-Bit]];
		delay_nms(1);
	}
}



