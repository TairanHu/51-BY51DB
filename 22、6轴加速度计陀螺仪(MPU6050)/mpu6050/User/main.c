/********************************************************

				6轴加速度计陀螺仪MPU6050实验
						
			采集MPU6050传感器数据,用OLED显示		

********************************************************/




#include "includes.h"


void main(void)
{
	
	Uart_Init(9600);    //串口初始化
	
	MPU6050_Init();		//6轴陀螺仪加速度计初始化
	
	OLED_Init();	    //OLED初始化
	

	MPU6050_Test();

	Show_f6x8str(0,2,"ACC_X  H");
	Show_f6x8str(81,2,"L");
	Show_f6x8str(0,3,"ACC_Y  H");
	Show_f6x8str(81,3,"L");
	Show_f6x8str(0,4,"ACC_Z  H");
	Show_f6x8str(81,4,"L");

	Show_f6x8str(0,5,"GYRO_X H");
	Show_f6x8str(81,5,"L");
	Show_f6x8str(0,6,"GYRO_Y H");
	Show_f6x8str(81,6,"L");
	Show_f6x8str(0,7,"GYRO_Z H");
	Show_f6x8str(81,7,"L");

	while(1)
	{

//		MPU6050_Read_All_Dat();	  //一次读取MPU6050全部数据

		Show_Num_f6x8(52,2,Device_Read_Byte(0xd0,ACCEL_XOUT_H),4);	   //读取X轴加速度计高8位数据
		Show_Num_f6x8(90,2,Device_Read_Byte(0xd0,ACCEL_XOUT_L),4);	   //读取X轴加速度计低8位数据
		Show_Num_f6x8(52,3,Device_Read_Byte(0xd0,ACCEL_YOUT_H),4);	   //读取Y轴加速度计高8位数据
		Show_Num_f6x8(90,3,Device_Read_Byte(0xd0,ACCEL_YOUT_L),4);	   //读取Y轴加速度计低8位数据
		Show_Num_f6x8(52,4,Device_Read_Byte(0xd0,ACCEL_ZOUT_H),4);	   //读取Z轴加速度计高8位数据
		Show_Num_f6x8(90,4,Device_Read_Byte(0xd0,ACCEL_ZOUT_L),4);	   //读取Z轴加速度计低8位数据

		Show_Num_f6x8(52,5,Device_Read_Byte(0xd0,GYRO_XOUT_H),4);	   //读取X轴陀螺仪高8位数据
		Show_Num_f6x8(90,5,Device_Read_Byte(0xd0,GYRO_XOUT_L),4);	   //读取X轴陀螺仪低8位数据
		Show_Num_f6x8(52,6,Device_Read_Byte(0xd0,GYRO_YOUT_H),4);	   //读取Y轴陀螺仪高8位数据
		Show_Num_f6x8(90,6,Device_Read_Byte(0xd0,GYRO_YOUT_L),4);	   //读取Y轴陀螺仪低8位数据
		Show_Num_f6x8(52,7,Device_Read_Byte(0xd0,GYRO_ZOUT_H),4);	   //读取Z轴陀螺仪高8位数据
		Show_Num_f6x8(90,7,Device_Read_Byte(0xd0,GYRO_ZOUT_L),4);	   //读取Z轴陀螺仪低8位数据

//		Show_Num_f6x8(10,7,Device_Read_Byte(0xd0,TEMP_OUT_H),5);	   //读取温度高8位数据
//		Show_Num_f6x8(50,7,Device_Read_Byte(0xd0,TEMP_OUT_L),5);	   //读取温度低8位数据


/****************************串口发送数据*****************************/

//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_XOUT_H));
//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_XOUT_L));
//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_YOUT_H));
//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_YOUT_L));
//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_ZOUT_H));
//		Uart_SendNum(Device_Read_Byte(0xd0,ACCEL_ZOUT_L));
//		UartSendStr("\r\n");
//
//		UartSendStr("test\r\n");
//
//		Delay_ms(100);

/*********************************************************************/
		
	}
}