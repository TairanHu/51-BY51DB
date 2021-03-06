/********************************************************

					动态数码管计数实验
						
	连接方法：P1口排针和8位数码管左侧排针用排线连接起来
		

********************************************************/

#include <reg52.h>

#define uchar unsigned char

sbit HC138A = P2^2;			//定义译码器输入端A  在 P2.2 管脚上
sbit HC138B = P2^3;			//定义译码器输入端B  在 P2.3 管脚上
sbit HC138C = P2^4;			//定义译码器输入端C  在 P2.4 管脚上			

uchar code table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

//uchar code dispbit[]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdF, 0xbF, 0x7F};    //位选控制   查表的方法控制

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
//	int Bit = 0;   //控制位选

	int count = 10;
	int High = 0, Low = 0;
	uchar LED_Out[8] = {0x00};
	
	while(1)
	{
		if(Low >= 10000)
		{
			High++;						//万位增加
			Low = 0;
		}

		LED_Out[0] = Low%10;			//取出数字个位
		LED_Out[1] = Low/10%10;			//取出数字十位
		LED_Out[2] = Low/100%10;		//取出数字百位
		LED_Out[3] = Low/1000%10;		//取出数字千位

		LED_Out[4] = High%10;			//取出数字万位
		LED_Out[5] = High/10%10;		//取出数字十万位
		LED_Out[6] = High/100%10;		//取出数字百万位
		LED_Out[7] = High/1000%10;		//取出数字千万位


		
		count = 10;
		while(count--)
		{
			HC138C = 0; HC138B = 0; HC138A = 0; 	//选中数码管第一位
			P1 = table[LED_Out[7]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
			                                        
			HC138C = 0; HC138B = 0; HC138A = 1;     //选中数码管第二位
			P1 = table[LED_Out[6]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
	                                                
			HC138C = 0; HC138B = 1; HC138A = 0;     //选中数码管第三位
			P1 = table[LED_Out[5]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
	                                                
			HC138C = 0; HC138B = 1; HC138A = 1;     //选中数码管第四位
			P1 = table[LED_Out[4]];                 //显示数字
			delay_nms(1);                           //延时
	                                                
			HC138C = 1; HC138B = 0; HC138A = 0;     //选中数码管第五位
			P1 = table[LED_Out[3]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
	                                                
			HC138C = 1; HC138B = 0; HC138A = 1;     //选中数码管第六位
			P1 = table[LED_Out[2]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
	                                                
			HC138C = 1; HC138B = 1; HC138A = 0;     //选中数码管第七位
			P1 = table[LED_Out[1]];                 //显示数字
			delay_nms(1);                           //延时
	                                                
			HC138C = 1; HC138B = 1; HC138A = 1;     //选中数码管第八位
			P1 = table[LED_Out[0]];                 //显示数字
			delay_nms(1);                           //延时
			P1 = 0x00;								//消影
		}

		Low++;		//数值增加
						
	}
}







