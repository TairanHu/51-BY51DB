#include "myiic.h"	  

//��ʼ��IIC
void IIC_Init(void)
{					     
 	IIC_SCL=1;
	IIC_SDA=1;
}


//����IIC��ʼ�ź�
void IIC_Start(void)
{

	IIC_SDA=1;	  	  
	IIC_SCL=1;
	//delay_us(1);
	_nop_();
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	//delay_us(1);
	_nop_();
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{

	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	//delay_us(1);
	_nop_();
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	//delay_us(1);	
	_nop_();	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)	//��һ���͵����ݿ�
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
//������ACKӦ��		    
void IIC_NAck(void)	   //��һ���ߵ����ݿ�
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uchar txd)
{                        
    uchar t;   
 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		//delay_us(1);   //��TEA5767��������ʱ���Ǳ����
		_nop_();
		IIC_SCL=1;
		//delay_us(1); 
		_nop_();
		IIC_SCL=0;	
		//delay_us(1);
		_nop_();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

void Device_Write_Byte(uchar DevAdd,uchar add,uchar dat)		//дһ���ֽ�
{
	IIC_Start();
	IIC_Send_Byte(DevAdd);//д���豸ID��д�ź�
	IIC_Wait_Ack();

	IIC_Send_Byte(add);//д��ַ
	IIC_Wait_Ack();

	IIC_Send_Byte(dat);
	IIC_Wait_Ack();

	IIC_Stop();
	//delay_ms(10);		
}

uchar Device_Read_Byte(uchar DevAdd,uchar add)			//��һ���ֽ�
{
	uchar IIC_DATA=0;
	IIC_Start();
	IIC_Send_Byte(DevAdd);//д���豸ID��д�ź�
	IIC_Wait_Ack();
	IIC_Send_Byte(add);//д��ַ
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(DevAdd+1);//д���豸ID�����ź�
	IIC_Wait_Ack();

	IIC_DATA=IIC_Read_Byte(0);//������ݣ�������ACK
	IIC_Stop();//
	return IIC_DATA;		
} 



























