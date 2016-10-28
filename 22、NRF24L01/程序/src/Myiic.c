#include "myiic.h"	  

//初始化IIC
void IIC_Init(void)
{					     
 	IIC_SCL=1;
	IIC_SDA=1;
}


//产生IIC起始信号
void IIC_Start(void)
{

	IIC_SDA=1;	  	  
	IIC_SCL=1;
	//delay_us(1);
	_nop_();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	//delay_us(1);
	_nop_();
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{

	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	//delay_us(1);
	_nop_();
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	//delay_us(1);	
	_nop_();	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uchar IIC_Wait_Ack(void)
{
	uchar ucErrTime=0;  
	IIC_SDA=1;//delay_us(1);
	_nop_();	   
	IIC_SCL=1;//delay_us(1);
	_nop_();
 
	while(IIC_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)	//送一个低到数据口
{
	IIC_SCL=0;
	
	IIC_SDA=0;
	//delay_us(1);
	_nop_();
	IIC_SCL=1;
	//delay_us(1);
	_nop_();
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)	   //送一个高到数据口
{
	IIC_SCL=0;
	
	IIC_SDA=1;
	//delay_us(1);
	_nop_();
	IIC_SCL=1;
	//delay_us(1);
	_nop_();
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uchar txd)
{                        
    uchar t;   
 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		//delay_us(1);   //对TEA5767这三个延时都是必须的
		_nop_();
		IIC_SCL=1;
		//delay_us(1); 
		_nop_();
		IIC_SCL=0;	
		//delay_us(1);
		_nop_();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uchar IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        //delay_us(1);
		_nop_();
		IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;   
		//delay_us(1); 
		_nop_();
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

void Device_Write_Byte(uchar DevAdd,uchar add,uchar dat)		//写一个字节
{
	IIC_Start();
	IIC_Send_Byte(DevAdd);//写入设备ID及写信号
	IIC_Wait_Ack();

	IIC_Send_Byte(add);//写地址
	IIC_Wait_Ack();

	IIC_Send_Byte(dat);
	IIC_Wait_Ack();

	IIC_Stop();
	//delay_ms(10);		
}

uchar Device_Read_Byte(uchar DevAdd,uchar add)			//读一个字节
{
	uchar IIC_DATA=0;
	IIC_Start();
	IIC_Send_Byte(DevAdd);//写入设备ID及写信号
	IIC_Wait_Ack();
	IIC_Send_Byte(add);//写地址
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(DevAdd+1);//写入设备ID及读信号
	IIC_Wait_Ack();

	IIC_DATA=IIC_Read_Byte(0);//获得数据，不发送ACK
	IIC_Stop();//
	return IIC_DATA;		
} 



























