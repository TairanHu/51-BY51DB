/********************************************************

					超声波实验
				
		LCD1602显示距离						
		连接方法：LCD1602直接插在1602的接口
			  
********************************************************/
#include<reg52.h>
//#include<delay.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

//sbit lcdrs=P2^5;
//sbit lcden=P2^3;
sbit trig=P3^6;               //超声波发送
sbit echo=P3^3;               //超声波接受
//P0____________DB0-DB7
uchar dis[]="Disp_HC-SR04";
uchar num[]="0123456789";
//uint distance;
uint timeh,timel,distance;
uint time;
//uchar timeH,timeL;
uchar succeed_flag = 0;
uchar flag = 0;
sbit test = P1^0;


sbit RS=P2^5;           //寄存器选择位，将RS位定义为P2.0引脚
sbit RW=P2^4;           //读写选择位，将RW位定义为P2.1引脚
sbit E=P2^3;            //使能信号位，将E位定义为P2.2引脚
sbit BF=P0^7;           //忙碌标志位，，将BF位定义为P0.7引脚

void delay(uint z)
{
 uint x,y;
  for(x=z;x>0;x--)
  for(y=110;y>0;y--);
}
//
void delay20us()
 { 
    uchar a ;
    for(a=0;a<100;a++);
 }

//延时1ms函数
void delay1ms()
{
	uchar i,j;	
 //	for(i=0;i<10;i++)
  	for(j=0;j<33;j++);	 
}
//延时nms函数
void delaynms(uchar n)
{
	uchar i;
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

void WriteString(uchar *dat)
{
	while(*dat != '\0')	
	{
		WriteData(*dat);
		dat++;
	}
}

//函数功能：对LCD的显示模式进行初始化设置
void LcdInitiate(void)
{
    delaynms(15);              
    WriteInstruction(0x38);    
	delaynms(5);               
    WriteInstruction(0x38);
	delaynms(5);               
	WriteInstruction(0x38);    
	delaynms(5);               
	WriteInstruction(0x0c);    
	delaynms(5);               
	WriteInstruction(0x06);    
	delaynms(5);               
	WriteInstruction(0x01);    
	delaynms(5);             

 }






void initime0()
{
	TMOD=0x01;
	TH0=0;
	TL0=0;
	EA=0;
	ET0=0;
	EX1=0;
}


void estern() interrupt 2
{
	timeh=TH0;
	timel=TL0;
//	beer();
	flag=1;						//进入中断，标志位就置1
	EX1=0;						//同时关断外部中断和定时器
    TR0=0;
}



void diaoyong()
	{
		uint i;
		uchar temp[3];
		uchar xiaoshu;
		EA=0;
		echo=1;					//为了检测电平的高低，首先必须拉高
		trig=1;
		delay20us();
		trig=0;
		while(echo==0);			//如果进入中断 即接收到超声波就向下执行
		flag=0;					//接收到就清除标志位
		EA=1;					//同时打开总中断
		EX1=1;					//打开外部中断
		TR0=1;					//开定时器
		TH0=0;					//定时器清零
		TL0=0;
		for(i=0;i<100;i++)		//等待测量的结果
		{
//			display(distance);	//用100次显示循环来延时，解决数码管显示不亮问题
		}
		delay(1);				//用延时函数数码管闪烁
		TR0=0;					//延时一段时间后关断定时器
		EX1=0;					//延时一段时间后关断外部中断
		if(flag==1)				//如果进入中断，说明测距已经测好
		{
			time=timeh*256+timel;//计算测定距离，并显示
			distance=time*0.1720;
//  			display(distance);
			
			temp[0] = distance/1000 + '0';
			temp[1] = distance%1000/100 + '0';
			temp[2] = distance%100/10 + '0';
			xiaoshu = distance%10 + '0';



			WriteAddress(0x02);  //写开始的显示地址,将在第1行第2列开始显示
			WriteString(temp) ;
			WriteData('.');
			WriteData(xiaoshu);
//			WriteString("kjafhjk") ;

			test=1;
		}
		if(flag==0)				//如果没有进入中断，距离为0，同时灯闪烁
		{
			distance=0;
			test=0;
		}
	}



void main()
{
	initime0();
	LcdInitiate();
	test=1;
	trig=0;
	EA=1;
	while(1)
	{
		diaoyong();
//		display(distance);
	
	}
}





