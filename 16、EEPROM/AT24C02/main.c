/********************************************************

						EEPROM实验
						
	向24C02中存入"Beyonday",同时读取出来并用LCD1602显示
		
********************************************************/

#include <reg52.h>
#include "2402.h"
#include "I2C.h"
#include "LCD1602.h"

#define  AT24C02 0xa0  //AT24C02 地址


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
 

void main()
{
	uchar pDat[] = "Beyonday";
	uchar Dat[11] ="";

   	Lcd1602_Init();       				  // 将液晶初始化

	ISendStr(AT24C02, 0, &pDat[0], 11);   // 向AT24C02中写入数据pDat[]
	delay_nms(100);						  // 延时
	IRcvStr(AT24C02, 0, &Dat[0], 11);	  // 将AT24C02中的数据读取出来保存在Dat[]数组中
	delay_nms(100);						  // 延时

	WriteAddress(0x00); 
	WriteString(Dat);					  //将读出来的数据用液晶显示

	while(1)							  //死循环
	{
	
	}
}






