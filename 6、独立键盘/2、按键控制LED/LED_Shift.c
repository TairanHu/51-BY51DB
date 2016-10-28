/********************************************************

					按键控制LED实验
						
		连接方法：P1口排针与LED排针用排线连接起来
				  P0口排针与按键BTJP用排线连接起来	
		

********************************************************/


#include <reg52.h>
#include <intrins.h>

sbit BUTTON1 = P0^0;	   //定义P0.0为1号按键接口
sbit BUTTON2 = P0^1;	   //定义P0.1为2号按键接口

void delay()
{
	int i,j;
	for(i = 0; i < 100; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}

//void main()
//{
//	unsigned char led = 0xfe;
//	P1 = led;
//	while(1)
//	{
//		if(BUTTON1 == 0)
//		{
//			delay();
//			if(BUTTON1 == 0)
//			{
//				led = _crol_(led, 1);		
//			}
//		}
//		else if(BUTTON2 == 0)
//		{
//			delay();
//			if(BUTTON2 == 0)
//			{
//				led = _cror_(led, 1);
//			}
//		}
//		
//		P1 = led;	
//	}
//}



void main()
{
	unsigned char led = 0xfe;
	P1 = led;		   					 //初始化P1为0xfe，最后一个端口输出低电平，其他输出高电平，即第一个LED点亮
	while(1)
	{
		if(BUTTON1 == 0)	             //如果第一个按键按下，LED就左移一位
		{
			delay();
			while(BUTTON1 == 0);

			delay();
//			if(BUTTON1 == 0)
			{
				led = _crol_(led, 1);		
			}
		}
		else if(BUTTON2 == 0)			  //如果第二个按键按下，LED 右移一位
		{
			delay();
			while(BUTTON2 == 0)	;
			delay();
//			if(BUTTON2 == 0)
			{
				led = _cror_(led, 1);
			}
		}
		
		P1 = led;	
	}
}
