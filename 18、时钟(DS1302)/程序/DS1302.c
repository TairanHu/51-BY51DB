/************************************************************
		主题：基于DS1302的日历时钟（万年历）
		时间：2011.12.20
************************************************************/
#include "DS1302.h"	 //包含DS1302头文件

uchar code num[10]={"0123456789"};   //液晶字符数组显示数字

sbit DATA=P3^5;   //位定义1302芯片的接口，数据输出端定义在P1.1引脚
sbit RST=P3^6;    //位定义1302芯片的接口，复位端口定义在P1.1引脚
sbit SCLK=P3^4;   //位定义1302芯片的接口，时钟输出端口定义在P1.1引脚

//延时
void delaynus(uchar n)
{
	uchar i;
	for(i=0;i<n;i++);       
}

//显示写1302
void Write1302(uchar dat)
{
	uchar i; 
	SCLK=0;                
	delaynus(2);           
	for(i=0;i<8;i++)       
	{
	    DATA=dat&0x01;   
		delaynus(2);     
		 SCLK=1;         
		 delaynus(2);    
		 SCLK=0;         
		 dat>>=1;        
	}
 }
//写命令
void WriteSet1302(uchar Cmd,uchar dat)
 {
	RST=0;          
	SCLK=0;         
	RST=1;         
	delaynus(2);   
	Write1302(Cmd);
	Write1302(dat);
	SCLK=1;        
	RST=0;         
 }

//读1302
 uchar Read1302(void)
 {
	uchar i,dat;
	delaynus(2);      
	for(i=0;i<8;i++)  
	{
		dat>>=1;       
		if(DATA==1)   
		dat|=0x80;   
		SCLK=1;      
		delaynus(2); 
		SCLK=0;      
		delaynus(2); 
	}
	DATA = 0;	 
	return dat;        //将读出的数据返回
}  

//复位1302
uchar  ReadSet1302(uchar Cmd)
 {
	uchar dat;
	RST=0;               
	SCLK=0;              
	RST=1;               
	Write1302(Cmd);      
	dat=Read1302();      
	SCLK=1;              
	RST=0;               
	return dat;          
}

//初始化1302
void Init_DS1302(void)
{	
	WriteSet1302(0x8E,0x00);                 //根据写状态寄存器命令字，写入不保护指令 
	WriteSet1302(0x80,((0/10)<<4|(0%10)));   //根据写秒寄存器命令字，写入秒的初始值
	WriteSet1302(0x82,((20/10)<<4|(20%10)));   //根据写分寄存器命令字，写入分的初始值
	WriteSet1302(0x84,((17/10)<<4|(17%10))); //根据写小时寄存器命令字，写入小时的初始值
	WriteSet1302(0x86,((30/10)<<4|(30%10))); //根据写日寄存器命令字，写入日的初始值
	WriteSet1302(0x88,((8/10)<<4|(8%10))); //根据写月寄存器命令字，写入月的初始值
	WriteSet1302(0x8c,((39/10)<<4|(39%10)));   //根据写小时寄存器命令字，写入小时的初始值



//	WriteSet1302(0x8E,0x00);                 //根据写状态寄存器命令字，写入不保护指令 
//	WriteSet1302(0x80,((0/10)<<4|(0%10)));   //根据写秒寄存器命令字，写入秒的初始值
//	WriteSet1302(0x82,((53/10)<<4|(53%10)));   //根据写分寄存器命令字，写入分的初始值
//	WriteSet1302(0x84,((20/10)<<4|(12%10))); //根据写小时寄存器命令字，写入小时的初始值
//	WriteSet1302(0x86,((26/10)<<4|(22%10))); //根据写日寄存器命令字，写入日的初始值
//	WriteSet1302(0x88,((1/10)<<4|(1%10))); //根据写月寄存器命令字，写入月的初始值
//	WriteSet1302(0x8c,((13/10)<<4|(13%10)));   //根据写小时寄存器命令字，写入小时的初始值

}
