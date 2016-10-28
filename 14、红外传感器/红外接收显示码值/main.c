/********************************************************

					红外接收实验
				
		LCD1602显示接收按键码值						
		连接方法：LCD1602直接插在1602的接口
			  
********************************************************/

#include "LCD1602.h"

#define uchar unsigned char
#define uint  unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

void delay(uchar x);  //x*0.14MS
void delay1(int ms);

sbit IRIN = P3^2;         //红外接收器数据线

uchar IRCOM[7];

void main()
{
	uchar Disp1[] = "IR Display";
	uchar Disp2[] = "IR-CODE: --H";
    
    IRIN=1;                    //I/O口初始化
	
    delay1(10);                 //延时
    LcdInitiate();                //初始化LCD             
    
	WriteAddress(0x03);    
    WriteAddress(0x03);                //设置显示位置为第一行的第1个字符
	WriteString(Disp1);

    WriteAddress(0x42);                //设置显示位置为第一行的第1个字符
	WriteString(Disp2);


	IE = 0x81;                 //允许总中断中断,使能 INT0 外部中断
	TCON = 0x01;               //触发方式为脉冲负边沿触发

   while(1)	;

} //end main



void IR_IN() interrupt 0 using 0
{
	unsigned char j,k,N=0;
	EX0 = 0;   
	delay(15);
	if (IRIN==1) 
	{ 
		EX0 =1;
		return;
	} 
	                           //确认IR信号出现
	while (!IRIN)            //等IR变为高电平，跳过9ms的前导低电平信号。
	{
		delay(1);
	}
	
	for (j=0;j<4;j++)         //收集四组数据
	{ 
		for (k=0;k<8;k++)        //每组数据有8位
		{
			while (IRIN)            //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
			{
				delay(1);
			}
			while (!IRIN)          //等 IR 变为高电平
			{
				delay(1);
			}
			while (IRIN)           //计算IR高电平时长
			{
				delay(1);
				N++;           
				if (N>=30)
				{ 
					EX0=1;
					return;
				}                  //0.14ms计数过长自动离开。
			}                        //高电平计数完毕                
			IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补“0”
			if (N>=8) 
			{
				IRCOM[j] = IRCOM[j] | 0x80;			//数据最高位补“1”
			}  
			N=0;
		}//end for k
	}//end for j
	   
	if (IRCOM[2]!=~IRCOM[3])
	{ 
		EX0=1;
		return; 
	}
	
	IRCOM[5]=IRCOM[2] & 0x0F;     //取键码的低四位
	IRCOM[6]=IRCOM[2] >> 4;       //右移4次，高四位变为低四位
	
	if(IRCOM[5]>9)
	{ 
		IRCOM[5]=IRCOM[5]+0x37;
	}
	else
	{
		IRCOM[5]=IRCOM[5]+0x30;
	}
	
	if(IRCOM[6]>9)
	{ 
		IRCOM[6]=IRCOM[6]+0x37;
	}
	else
	{
		IRCOM[6]=IRCOM[6]+0x30;
	}
	
	WriteAddress(0x4b);             
	WriteData(IRCOM[6]);        //第一位数显示 
	WriteAddress(0x4c);             
	WriteData(IRCOM[5]);        //第二位数显示
	
	EX0 = 1; 
} 

/**********************************************************/
/**********************************************************/
void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

/**********************************************************/
void delay1(int ms)
{
	unsigned char y;
	while(ms--)
	{
		for(y = 0; y<250; y++)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

