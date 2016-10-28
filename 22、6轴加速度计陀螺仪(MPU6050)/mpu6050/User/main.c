/********************************************************

				6����ٶȼ�������MPU6050ʵ��
						
			�ɼ�MPU6050����������,��OLED��ʾ		

********************************************************/




#include "includes.h"


void main(void)
{
	
	Uart_Init(9600);    //���ڳ�ʼ��
	
	MPU6050_Init();		//6�������Ǽ��ٶȼƳ�ʼ��
	
	OLED_Init();	    //OLED��ʼ��
	

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

//		MPU6050_Read_All_Dat();	  //һ�ζ�ȡMPU6050ȫ������

		Show_Num_f6x8(52,2,Device_Read_Byte(0xd0,ACCEL_XOUT_H),4);	   //��ȡX����ٶȼƸ�8λ����
		Show_Num_f6x8(90,2,Device_Read_Byte(0xd0,ACCEL_XOUT_L),4);	   //��ȡX����ٶȼƵ�8λ����
		Show_Num_f6x8(52,3,Device_Read_Byte(0xd0,ACCEL_YOUT_H),4);	   //��ȡY����ٶȼƸ�8λ����
		Show_Num_f6x8(90,3,Device_Read_Byte(0xd0,ACCEL_YOUT_L),4);	   //��ȡY����ٶȼƵ�8λ����
		Show_Num_f6x8(52,4,Device_Read_Byte(0xd0,ACCEL_ZOUT_H),4);	   //��ȡZ����ٶȼƸ�8λ����
		Show_Num_f6x8(90,4,Device_Read_Byte(0xd0,ACCEL_ZOUT_L),4);	   //��ȡZ����ٶȼƵ�8λ����

		Show_Num_f6x8(52,5,Device_Read_Byte(0xd0,GYRO_XOUT_H),4);	   //��ȡX�������Ǹ�8λ����
		Show_Num_f6x8(90,5,Device_Read_Byte(0xd0,GYRO_XOUT_L),4);	   //��ȡX�������ǵ�8λ����
		Show_Num_f6x8(52,6,Device_Read_Byte(0xd0,GYRO_YOUT_H),4);	   //��ȡY�������Ǹ�8λ����
		Show_Num_f6x8(90,6,Device_Read_Byte(0xd0,GYRO_YOUT_L),4);	   //��ȡY�������ǵ�8λ����
		Show_Num_f6x8(52,7,Device_Read_Byte(0xd0,GYRO_ZOUT_H),4);	   //��ȡZ�������Ǹ�8λ����
		Show_Num_f6x8(90,7,Device_Read_Byte(0xd0,GYRO_ZOUT_L),4);	   //��ȡZ�������ǵ�8λ����

//		Show_Num_f6x8(10,7,Device_Read_Byte(0xd0,TEMP_OUT_H),5);	   //��ȡ�¶ȸ�8λ����
//		Show_Num_f6x8(50,7,Device_Read_Byte(0xd0,TEMP_OUT_L),5);	   //��ȡ�¶ȵ�8λ����


/****************************���ڷ�������*****************************/

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