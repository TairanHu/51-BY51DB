
#include "DS18B20.h"


sbit D18B20=P3^7; // 18b20的引脚定义



bit  flag;
uint Temperature;	//用来存放读出温度后的值
uchar temp_buff[9]; //存储读取的字节，read scratchpad为9字节，read rom ID为8字节
uchar *p,TIM;


/************************************************************
*Function:延时处理
*parameter:
*Return:
*Modify:
*************************************************************/
void TempDelay (uchar us)
{
	while(us--);
}

/************************************************************
*Function:18B20初始化
*parameter:
*Return:
*Modify:
*************************************************************/
void Init18b20 (void)
{
	D18B20=1;
	_nop_();
	D18B20=0;
	TempDelay(80);   //delay 530 uS//80
	_nop_();
	D18B20=1;
	TempDelay(14);   //delay 100 uS//14
	_nop_();
	_nop_();
	_nop_();
	
	if(D18B20==0)
		flag = 1;   //detect 1820 success!
	else
		flag = 0;    //detect 1820 fail!
	TempDelay(20);       //20
	_nop_();
	_nop_();
	D18B20 = 1;
}

/************************************************************
*Function:向18B20写入一个字节
*parameter:
*Return:
*Modify:
*************************************************************/
void WriteByte (uchar wr)  //单字节写入
{
	unsigned char idata i;
	for (i=0;i<8;i++)
	{
		D18B20 = 0;
		_nop_();
		D18B20=wr&0x01;
		TempDelay(3);   //delay 45 uS //5
		_nop_();
		_nop_();
		D18B20=1;
		wr >>= 1;
	}
}

/************************************************************
*Function:读18B20的一个字节
*parameter:
*Return:
*Modify:
*************************************************************/
unsigned char ReadByte (void)     //读取单字节
{
	unsigned char idata i,u=0;
	for(i=0;i<8;i++)
	{
		D18B20 = 0;
		u >>= 1;
		D18B20 = 1;
		if(D18B20==1)
		u |= 0x80;
		TempDelay (2);
		_nop_();
	}
	return(u);
}

/************************************************************
*Function:读18B20
*parameter:
*Return:
*Modify:
*************************************************************/
void read_bytes (uchar j)
{
	 unsigned char idata i;
	 for(i=0;i<j;i++)
	 {
		  *p = ReadByte();
		  p++;
	 }
}

/************************************************************
*Function:读取温度
*parameter:
*Return:
*Modify:
*************************************************************/
void GemTemp (void)
{        
	    Temperature = temp_buff[1]*0x100 + temp_buff[0];
//	    Temperature *= 0.625;
		Temperature /= 16;
		TempDelay(1);
}

/************************************************************
*Function:18B20ID全处理
*parameter:
*Return:
*Modify:
*************************************************************/
void TemperatuerResult(void)
{
	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0x44);   //Temperature convert

	Init18b20 ();
	WriteByte(0xcc);   //skip rom
	WriteByte(0xbe);   //read Temperature
	p = temp_buff;
	read_bytes (9);
	GemTemp();
}


void GetTemp()
{       
     if(TIM==100) //每隔 1000ms 读取温度
	{  TIM=0;
	   TemperatuerResult();
	}
}

/*************************************
 [ t1 (10ms)中断] 中断
*************************************/
void T1zd(void) interrupt 3 
{
   TH1 = 0xD8;    //10
   TL1 = 0xF0;
   TIM++;

}
