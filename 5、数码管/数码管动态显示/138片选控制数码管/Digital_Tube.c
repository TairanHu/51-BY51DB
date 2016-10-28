/********************************************************

					动态数码管实验
						
	连接方法：P1口排针和8位数码管左侧排针用排线连接起来
		

********************************************************/

#include <reg52.h>

#define uchar unsigned char

sbit HC138A = P2^2;			//定义译码器输入端A  在 P2.2 管脚上
sbit HC138B = P2^3;			//定义译码器输入端B  在 P2.3 管脚上
sbit HC138C = P2^4;			//定义译码器输入端C  在 P2.4 管脚上			

uchar code table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

//uchar code dispbit[]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdF, 0xbF, 0x7F};    //位选控制   查表的方法控制



/*****************   延时函数  ********************/
void delay_nms(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}


/*****************   主函数  ********************/
void main()
{
//	int Bit = 0;   //控制位选
	while(1)
	{
		HC138C = 0; HC138B = 0; HC138A = 0;		//选中数码管第一位
		P1 = table[0];							//显示数字0
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 0; HC138B = 0; HC138A = 1; 	//选中数码管第二位
		P1 = table[1];							//显示数字1
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 0; HC138B = 1; HC138A = 0; 	//选中数码管第三位
		P1 = table[2];							//显示数字2
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 0; HC138B = 1; HC138A = 1; 	//选中数码管第四位
		P1 = table[3];							//显示数字3
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 1; HC138B = 0; HC138A = 0; 	//选中数码管第五位
		P1 = table[4];							//显示数字4
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 1; HC138B = 0; HC138A = 1; 	//选中数码管第六位
		P1 = table[5];							//显示数字5
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 1; HC138B = 1; HC138A = 0; 	//选中数码管第七位
		P1 = table[6];							//显示数字6
		delay_nms(1);							//延时
		P1 = 0x00;								//消影

		HC138C = 1; HC138B = 1; HC138A = 1; 	//选中数码管第八位
		P1 = table[7];							//显示数字7
		delay_nms(1);							//延时
		P1 = 0x00;								//消影
	}
}

