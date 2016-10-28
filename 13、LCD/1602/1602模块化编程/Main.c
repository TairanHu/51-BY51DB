/********************************************************

				LCD1602模块化实验
				
		LCD1602显示"LCD1602 TEST"和"By Beyonday"						
		连接方法：LCD1602直接插在1602的接口
			  
********************************************************/

#include <reg52.h>
#include "1602.h"    //包含LCD1602头文件

uchar temp[] = "LCD1602 TEST";	
uchar temp1[] = "By Beyonday";

//主函数
void main(void)
{


	LcdInitiate();       //将液晶初始化
	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  //写开始的显示地址,将在第1行第2列开始显示
	WriteString(temp) ;
	WriteAddress(0x45);  //写temp1的显示地址， 显示在第2行第6列
	WriteString(temp1) ;

   	
	while(1)	         //死循环
	{
		

	}
}


