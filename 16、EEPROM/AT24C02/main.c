/********************************************************

						EEPROMʵ��
						
	��24C02�д���"Beyonday",ͬʱ��ȡ��������LCD1602��ʾ
		
********************************************************/

#include <reg52.h>
#include "2402.h"
#include "I2C.h"
#include "LCD1602.h"

#define  AT24C02 0xa0  //AT24C02 ��ַ


/***********************************************

	   ��ʱ����    ��ʱʱ�����Ϊn����

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

   	Lcd1602_Init();       				  // ��Һ����ʼ��

	ISendStr(AT24C02, 0, &pDat[0], 11);   // ��AT24C02��д������pDat[]
	delay_nms(100);						  // ��ʱ
	IRcvStr(AT24C02, 0, &Dat[0], 11);	  // ��AT24C02�е����ݶ�ȡ����������Dat[]������
	delay_nms(100);						  // ��ʱ

	WriteAddress(0x00); 
	WriteString(Dat);					  //����������������Һ����ʾ

	while(1)							  //��ѭ��
	{
	
	}
}






