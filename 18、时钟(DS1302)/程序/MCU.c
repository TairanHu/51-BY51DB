/************************************************************
		
		基于DS1302的日历时钟（万年历）

		写入时间，并采用LCD1602显示时间	
		实时时钟旁的排针用跳线帽短路	
************************************************************/
#include "DS1302.h"     //包含单片机寄存器的头文件
#include "LCD1602.h"    //包含LCD1602头文件
extern uchar code num[10];
//显示秒
uchar second,minute,hour,day,month,year;      
uchar ReadValue;     //储存从1302读取的数据
uchar pic=0,num1=0,num2=0;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f};

void DisplaySecond(uchar x)
{
 	uchar i,j;     //j,k,l分别储存数字的十位和个位
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x49);    
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);           
}

//显示分
void DisplayMinute(uchar x)
{
 	uchar i,j;     
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x46);    
	WriteData(num[i]);  
	WriteData(num[j]);   
	delaynms(50);           
}

//显示时
void DisplayHour(uchar x)
{
 	uchar i,j;     //j,k,l分别储存温度的百位、十位和个位
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x43);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);           
}

//显示日
void DisplayDay(uchar x)
{
 uchar i,j;     //j,k,l分别储存温度的百位、十位和个位
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x0a);    
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
}

//显示月
void DisplayMonth(uchar x)
{
 	uchar i,j;     //j,k,l分别储存温度的百位、十位和个位
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x07);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
 }

//显示年
void DisplayYear(uchar x)
{
 	uchar i,j;     //j,k,l分别储存温度的百位、十位和个位
	i=x/10;//取十位
	j=x%10;//取个位     
	WriteAddress(0x04);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
}

//主函数
void main(void)
{
	
	
	LcdInitiate();       //将液晶初始化
	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  //写Date的显示地址,将在第1行第2列开始显示
	WriteData('2');      //将字符常量写入LCD
	WriteData('0');      //将字符常量写入LCD
	WriteAddress(0x06);  //写年月分隔符的显示地址， 显示在第1行第9列
	WriteData('-');      //将字符常量写入LCD
	WriteAddress(0x09);  //写月日分隔符的显示地址， 显示在第1行第12列
	WriteData('-');      //将字符常量写入LCD
	WriteAddress(0x45);  //写小时与分钟分隔符的显示地址， 显示在第2行第6列
	WriteData(':');      //将字符常量写入LCD
	WriteAddress(0x0d);  //写分钟与秒分隔符的显示地址， 显示在第2行第9列
	WriteData('^');      //将字符常量写入LCD
	WriteData('_');      //将字符常量写入LCD
	WriteData('^');      //将字符常量写入LCD
	WriteAddress(0x48);  //写分钟与秒分隔符的显示地址， 显示在第2行第9列
	WriteData(':');      //将字符常量写入LCD  
	WriteAddress(0x4d);  //写分钟与秒分隔符的显示地址， 显示在第2行第9列
	WriteData('^');      //将字符常量写入LCD
	WriteData('o');      //将字符常量写入LCD
	WriteData('^');      //将字符常量写入LCD
	Init_DS1302();       //将1302初始化
	

   	
	while(1)
	{
		

	{
		
	    ReadValue = ReadSet1302(0x81);   //从秒寄存器读数据
		second=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);//将读出数据转化
		DisplaySecond(second);          //显示秒
		
		 ReadValue = ReadSet1302(0x83);  //从分寄存器读
		minute=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //将读出数据转化
		DisplayMinute(minute);	       //显示分
		 ReadValue = ReadSet1302(0x85);  //从分寄存器读
		hour=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //将读出数据转化
		DisplayHour(hour);	             //显示小时
		ReadValue = ReadSet1302(0x87);  //从分寄存器读
		day=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //将读出数据转化
		DisplayDay(day);                //显示日
		ReadValue = ReadSet1302(0x89);  //从分寄存器读
		month=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //将读出数据转化
		DisplayMonth(month);            //显示月
		ReadValue = ReadSet1302(0x8d);  //从分寄存器读
		year=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //将读出数据转化
		DisplayYear(year);              //显示年  
	}
	}
}


