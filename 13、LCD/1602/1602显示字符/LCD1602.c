/********************************************************

					LCD1602实验
				
		LCD1602显示"LCD1602 TEST"和"By Beyonday"						
		连接方法：LCD1602直接插在1602的接口
			  
********************************************************/


#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
  
sbit RS=P2^5;           //寄存器选择位，将RS位定义为P2.0引脚
sbit RW=P2^4;           //读写选择位，将RW位定义为P2.1引脚
sbit E=P2^3;            //使能信号位，将E位定义为P2.2引脚
sbit BF=P0^7;           //忙碌标志位，，将BF位定义为P0.7引脚
//延时1ms函数
void delay1ms()
{
	uchar i,j;	
 //	for(i=0;i<10;i++)
  	for(j=0;j<33;j++);	 
}
//延时nms函数
void delaynms(int n)
{
	int i;
	for(i=0;i<n;i++)
   	delay1ms();
}

//函数功能：判断液晶模块的忙碌状态，返回值：result。result=1，忙碌;result=0，不忙
bit BusyTest(void)
{
    bit result;
	RS=0;       //根据规定，RS为低电平，RW为高电平时，可以读状态
    RW=1;
    E=1;        //E=1，才允许读写
    _nop_();   //空操作
    _nop_();
    _nop_(); 
    _nop_();   //空操作四个机器周期，给硬件反应时间	
    result=BF;  //将忙碌标志电平赋给result
    E=0;         //将E恢复低电平
    return result;
}

//函数功能：将模式设置指令或显示地址写入液晶模块
void WriteInstruction (uchar dictate)
{   
    while(BusyTest()==1);  
	 RS=0;                 
	 RW=0;   
	 E=0;                  
                           
	 _nop_();
	 _nop_();              
	 P0=dictate;           
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();              
	 E=1;                  
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();              
	  E=0;                 
 }

//函数功能：指定字符显示的实际地址
void WriteAddress(uchar x)
{
    WriteInstruction(x|0x80); //显示位置的确定方法规定为"80H+地址码x"
}

//函数功能：将数据(字符的标准ASCII码)写入液晶模块
void WriteData(uchar y)
{
    while(BusyTest()==1);  
	  RS=1;           
	  RW=0;
	  E=0;         
                   
	  P0=y;        
	  _nop_();
	  _nop_();
 	  _nop_();
     _nop_();      
	  E=1;         
	  _nop_();
	  _nop_();
	  _nop_();
	 _nop_();      
	 E=0;          
}

void WriteString(uchar *a)
{
	while(*a != '\0')	
	{
		WriteData(*a);
		a++;
	}
}

//函数功能：对LCD的显示模式进行初始化设置
void LcdInitiate(void)
{
    delaynms(15);              
    WriteInstruction(0x38);    //16*2显示，5*7点阵，8位数据
	delaynms(5);               
    WriteInstruction(0x38);
	delaynms(5);               
	WriteInstruction(0x38);    
	delaynms(5);               
	WriteInstruction(0x0c);    //显示开，关光标
	delaynms(5);               
	WriteInstruction(0x06);    //移动光标
	delaynms(5);               
	WriteInstruction(0x01);    //清除LCD的显示内容
	delaynms(5);             

 }

 void main(void)
{

	uchar temp[] = "LCD1602 TEST";	
	uchar temp1[] = "By Beyonday";

	int i = 0;

	LcdInitiate();       //将液晶初始化
//	WriteAddress(0x00);
//	WriteData(' ');
//	WriteAddress(0x02);  //写开始的显示地址,将在第1行第2列开始显示
//	WriteString(temp) ;
//	WriteAddress(0x45);  //写temp1的显示地址， 显示在第2行第6列
//	WriteString(temp1) ;

   	
	while(1)	         //死循环
	{
			WriteAddress(0x00);
			WriteData(' ');
			WriteAddress(0x02);  //写开始的显示地址,将在第1行第2列开始显示
			while(temp[i] != '\0')
			{
				WriteData(temp[i]);
				i++;
				delaynms(1000);	
			}
			i = 0;
			WriteAddress(0x45);  //写temp1的显示地址， 显示在第2行第6列
			while(temp1[i] != '\0')
			{
				WriteData(temp1[i]);
				i++;
				delaynms(1000);	
			}
			i = 0;
			WriteInstruction(0x01); 

			delaynms(1000);
		

	}
}



