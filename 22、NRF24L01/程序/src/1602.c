#include "1602.h"

void LCD1602_Test(void)
{
	LCD1602_ShowString(2,2,"Beyonday Studio");
	//LCD1602_ShowString(1,2,"1602 Test Pass");

//	LCD1602_ShowNum(1,1,12345,5);
//	LCD1602_ShowNum(1,2,12345,5);

}

void LCD1602_Init(void)
{
	LCD1602_WriteCom(0x38);//8位数据接口，两行显示，5*7点阵
	//delay_ms(5);
	LCD1602_WriteCom(0x0c);//打开显示，关闭光标，光标不闪烁
	//delay_ms(5);
	LCD1602_WriteCom(0x06);//读写操作后，光标自动增一，画面不动
	//delay_ms(5);
	LCD1602_WriteCom(0x01);//清屏
	//delay_ms(5);
	LCD1602_WriteCom(0x80);
}

bit LCD1602_Busy(void)
{                          
	bit result;
	LCD1602_RS = 0;
	LCD1602_RW = 1;//读
	LCD1602_LCDE = 1;
	Delay_ms(1);
	result = (bit)(P0&0x80);
	LCD1602_LCDE = 0;
	return result; 
}
void LCD1602_WriteCom(uchar com) //写命令
{
	//while(lcd_busy());
	LCD1602_RW=0;//写
	LCD1602_RS=0;//命令
	LCD1602_DATA=com;
	Delay_ms(1);
	LCD1602_LCDE=1;
	Delay_ms(1);
	LCD1602_LCDE=0;
}
void LCD1602_WriteData(uchar date)	  //写数据
{
	//while(lcd_busy());
	LCD1602_RW=0;//写
	LCD1602_RS=1;//数据
	LCD1602_DATA=date;
	Delay_ms(1);
	LCD1602_LCDE=1;
	Delay_ms(1);
	LCD1602_LCDE=0;
}


void LCD1602_ShowString(uchar x,uchar y,uchar *ch)//字符显示
{
	uchar i=0;
	if(y==1)LCD1602_WriteCom(0x80+x-1);

	else if(y==2)LCD1602_WriteCom(0x80+0x40+x-1);

	while(ch[i]!='\0')
	{
		LCD1602_WriteData(ch[i]);
		i++;
	}		
}


uint MyPow(uint m,uint n)//m^n
{
	uint result=1;
	while(n--)
	result*=m;
	return result;

}
void LCD1602_ShowNum(uchar x,uchar y,uint num,uchar len)
{
	uchar temp,i;
	if(y==1)
	LCD1602_WriteCom(0x80+x-1);

	else if(y==2)
	 LCD1602_WriteCom(0x80+0x40+x-1);

	for(i=0;i<len;i++)
	{
		temp=(num/MyPow(10,len-i-1))%10;//获取单个数字
		LCD1602_WriteData(0x30+temp);	
	}	
}