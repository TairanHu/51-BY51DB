/********************************************************

						按键实验
						
		连接方法：P1口排针与LED排针用排线连接起来
				  P0口排针与按键BTJP用排线连接起来	
		

********************************************************/
#include <reg52.h>

sbit BUTTON = P0^0;         //定义按键在P0.0端口上
sbit LED = P1^0;            //定义LED在P1.0端口上

void main()
{
	while(1)
	{
		if(BUTTON == 0)		//当按键按下时，单片机对应引脚变成低电平，LED点亮
		{
			LED = 0;
		}			
		else 				//当按键松开时，单片机对应引脚变成高电平，LED熄灭
		{
			LED = 1;
		}	
	}
}