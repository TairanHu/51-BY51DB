/********************************************************

						74LS595移位实验
						
		连接方法：P0口连接移位寄存器(并转串)U8JP1
				  P2口连接LED排针DJP
		
********************************************************/

#include <reg52.h> 
#include <intrins.h>
#define  NOP() _nop_()  /* 定义空指令 */

//SPI IO
sbit MOSIO =P3^5;
sbit R_CLK =P3^6;
sbit S_CLK =P3^4;


void delay(unsigned int i);      //函数声名
void HC595SendData(unsigned char SendVal);
 

void main()
{
	unsigned char Led=0xfe;	 //1111 1110
	HC595SendData(0xff);	    //初始化595使他为高电平 让LED处于熄灭状态
	   
	while(1)
	{	   	
		HC595SendData(Led);	//调用595驱动程序 把LED的数据送到595
		Led<<=1;
		Led	= Led| 0x01;  //移位后，后面的位为高电平;
		if (Led == 0xff ) Led=0xfe;  //1111 1110
		delay(300);
	 
}   
}	
/*****************************************************************************
*  延时子程序															     *
*																			 *
******************************************************************************/
void delay(unsigned int i)
{
    unsigned int j;
    for(i; i > 0; i--)
        for(j = 110; j > 0; j--);
}


/*********************************************************************************************************
** 函数名称: HC595SendData
** 功能描述: 向SPI总线发送数据
*********************************************************************************************************/
void HC595SendData(unsigned char SendVal)
{  
	unsigned char i;
		
	for(i=0;i<8;i++) 
	{
		if((SendVal<<i)&0x80) MOSIO=1; //set dataline high  0X80  最高位与SendVal左移的最高位 进行逻辑运算
		else MOSIO=0;				   // 如果为真 MOSIO = 1  
		 
		S_CLK=0;
		NOP();	//产生方形波
		NOP();
		S_CLK=1;	
	}
	   
		
	R_CLK=0; //set dataline low
	NOP();   //产生方形波
	NOP();
	R_CLK=1; //片选

}

