#include "mpu6050.h"

void MPU6050_Test(void)
{
	uchar temp=0;
	temp=Device_Read_Byte(Mpu6050_IIC_ADD,WHO_AM_I);
	
	if(temp==Mpu6050_ID)
	{
		Show_f8x16str(0,0,"6050 Test Pass!");
//		Show_f8x16str(0,2,"ID:");
//		Show_Num_f8x16(24,2,temp,3);
	}
	else
	{
		Show_f8x16str(0,0,"MPU6050 Test Fail!");
//		Show_f8x16str(0,2,"ID:");
//		Show_Num_f8x16(24,2,temp,3);
	}
}

void MPU6050_Init(void)				 //MPU6050��ʼ��
{
	IIC_Init();
	Device_Write_Byte(0xd0,PWR_MGMT_1,0x00);//������ߣ������ڲ��¶ȴ�������ʹ���ڲ�8M����
	Device_Write_Byte(0xd0,SMPLRT_DIV,0x07);//���ò������ʷ�ƵΪ8��Ƶ��1k/8=125hz
	Device_Write_Byte(0xd0,CONFIG,0x06);//���õ�ͨ�˲�������Ϊ5HZ�����������Ƶ��Ϊ1Khz
	Device_Write_Byte(0xd0,GYRO_CONFIG, 0x18);//���������ǲ�����Χ+-2000��/s�����Լ�
	Device_Write_Byte(0xd0,ACCEL_CONFIG,0x09);//���ü��ٶȼƷ�ΧΪ+��4g�����Լ죬��ͨ�˲�������Ƶ��Ϊ5hz	
	Delay_ms(10);
}

void MPU6050_Read_All_Dat(void)   //������ȡ
{
	uchar i;
	IIC_Start();
	IIC_Send_Byte(0xd0);//д���豸ID��д�ź�
	IIC_Wait_Ack();
	IIC_Send_Byte(ACCEL_XOUT_H);//д��ַ
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(0xd1);//д���豸ID�����ź�
	IIC_Wait_Ack();

	for(i=0;i<13;i++)
	{
		MPU6050_Data[i]=IIC_Read_Byte(1);//������ݣ�����ACK
		delay_us();
	}
	MPU6050_Data[13]=IIC_Read_Byte(0);

	IIC_Stop();//			
}  
