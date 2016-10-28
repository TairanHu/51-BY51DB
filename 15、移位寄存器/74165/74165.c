/********************************************************

						74LS165移位实验
						
		连接方法：P0口连接移位寄存器(并转串)U8JP1
				  P2口连接LED排针DJP
		
********************************************************/
#include <reg52.H>
#include <intrins.h> 

#define  NOP()   _nop_()   /* 定义空指令 */

//SPI 接口
sbit    CLK    = P1^7;	   //串行时钟
sbit    IN_PL  = P1^6;    //把数据加载到锁存器中
sbit    IN_Dat = P3^5;    //数据通过P1.7脚移进单片机内处理

unsigned long ReHC74165(void);	 //函数声名 
 

 /********************************************************
 *	主函数												 *
 *														 *
 ********************************************************/
 void main()
 {	  	 
	 unsigned long  Input;	
	 P0 = 0x7e;

	 while(1)
	 { 
		 Input=ReHC74165();//调用165驱动程序

		 P2 = Input;	  //清除
	 }    
 }


 
 /*************************此部分为74HC165的驱动程序使用SPI总线连接*************************************/


unsigned long ReHC74165(void)
{  
	unsigned char i;
	unsigned int indata;
			
	IN_PL=0;
	NOP();    	 //短暂延时 产生一定宽度的脉冲
	IN_PL=1;	 //将外部信号全部读入锁存器中
	NOP(); 
	              
	indata=0;   //保存数据的变量清0  
	for(i=0; i<8; i++)
	{ 
		indata=indata<<1;	 //左移一位
		if(IN_Dat==1)indata=indata+1;	//如果IN_Dat检测到高电平 保存数据的变量加1 
		CLK=0;   //时钟置0
		NOP();
		CLK=1;   //时钟置1	  
	} 
	 
	return(indata);	 //将保存数据的变量返回
}



