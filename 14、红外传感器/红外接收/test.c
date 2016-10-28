/********************************************************

					红外接收实验
				
		LED状态翻转显示是否接收到红外信号					
		连接方法：P1口连接LED
			  
********************************************************/

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

sbit IRIN = P3^2;         //红外接收器数据线

uchar LED ;

void delay(uchar x);  //x*0.14MS
void delay1(int ms); 


/*******************************************************************/
void main()
{   
    IRIN=1;                    //I/O口初始化
	LED = 0xaa;
	P1 = LED;

	IE = 0x81;                 //允许总中断中断,使能 INT0 外部中断
	TCON = 0x01;               //触发方式为脉冲负边沿触发

    while(1)
	{
	
	}


} //end main
/**********************************************************/
void IR_IN() interrupt 0 using 0
{	
	EX0 = 0;   		  //关掉外部中断防止中断的再次发生进入检测引导码阶段（9ms的低电平4.5ms的高电平）
	delay(15);
	if (IRIN==1) 
	{
		EX0 =1;			  //9ms的检测检测结束从新打开外部中断
		return;
	} 
	                           //确认IR信号出现
	while (!IRIN)            //等IR变为高电平，跳过9ms的前导低电平信号。
	{
		delay(1);
	}
	
	LED = ~LED;
	P1 = LED;
	
	EX0 = 1;
}


/**********************************************************/
void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

/**********************************************************/
void delay1(int ms)
{
	unsigned char y;
	while(ms--)
	{
		for(y = 0; y<250; y++)
		{
		   _nop_();
		   _nop_();
		   _nop_();
		   _nop_();
		}
	}
}

