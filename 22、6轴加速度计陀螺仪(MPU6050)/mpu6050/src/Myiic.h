#ifndef __MYIIC_H
#define __MYIIC_H
#include "includes.h"	  
  	   		   
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uchar txd);			//IIC����һ���ֽ�
uchar IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uchar IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uchar daddr,uchar addr,uchar dat);
uchar IIC_Read_One_Byte(uchar daddr,uchar addr);	 

uchar Device_Read_Byte(uchar DevAdd,uchar add);
void Device_Write_Byte(uchar DevAdd,uchar add,uchar dat);
 
#endif
















