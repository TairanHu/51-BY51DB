/**************************************************
				外部中断实验
		使用外部中断0，来实现点亮LED的效果

***************************************************/

#include < reg52.h >
#include <intrins.h>

void delay(unsigned int i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}

void main(void)
{  

// IT0=0;       //低电平触发
   IT0=1;       //下降沿触发
   EX0=1;

   EA=1;


   while(1)
   {    

   }

}



/********************************************************
* INT0中断函数                                          *
********************************************************/
void  counter0(void) interrupt 0
{
  
   EX0=0;		   //关闭外部中断
   delay(100);	   //延时
   P0 = 0x00;	   //点亮LED
   EX0=1;		   //打开外部中断
}


