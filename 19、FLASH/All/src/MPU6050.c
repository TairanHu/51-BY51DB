#include "mpu6050.h"

void MPU6050_Test(void)
{
	uchar temp=0;
	temp=Device_Read_Byte(Mpu6050_IIC_ADD,WHO_AM_I);
	
	if(temp==Mpu6050_ID)
	{
		Show_f8x16str(0,0,"6050 Test Pass!");
		Show_f8x16str(0,2,"ID:");
		Show_Num_f8x16(24,2,temp,3);
	}
	else
	{
		Show_f8x16str(0,0,"MPU6050 Test Fail!");
		Show_f8x16str(0,2,"ID:");
		Show_Num_f8x16(24,2,temp,3);
	}
}

void MPU6050_Init(void)				 //MPU6050初始化
{
	IIC_Init();
	Device_Write_Byte(0xd0,PWR_MGMT_1,0x00);//解除休眠，开启内部温度传感器，使用内部8M晶振
	Device_Write_Byte(0xd0,SMPLRT_DIV,0x07);//设置采样速率分频为8分频，1k/8=125hz
	Device_Write_Byte(0xd0,CONFIG,0x06);//设置低通滤波器带宽为5HZ，陀螺仪输出频率为1Khz
	Device_Write_Byte(0xd0,GYRO_CONFIG, 0x18);//设置陀螺仪测量范围+-2000度/s，不自检
	Device_Write_Byte(0xd0,ACCEL_CONFIG,0x09);//设置加速度计范围为+—4g，不自检，高通滤波器截至频率为5hz	
	Delay_ms(10);
}

void MPU6050_Read_All_Dat(void)   //连续读取
{
	uchar i;
	IIC_Start();
	IIC_Send_Byte(0xd0);//写入设备ID及写信号
	IIC_Wait_Ack();
	IIC_Send_Byte(ACCEL_XOUT_H);//写地址
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(0xd1);//写入设备ID及读信号
	IIC_Wait_Ack();

	for(i=0;i<13;i++)
	{
		MPU6050_Data[i]=IIC_Read_Byte(1);//获得数据，发送ACK
	}
	MPU6050_Data[13]=IIC_Read_Byte(0);

	IIC_Stop();//			
}  
