#ifndef __MYIIC_H
#define __MYIIC_H
#include "includes.h"	  
  	   		   
//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uchar txd);			//IIC发送一个字节
uchar IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uchar IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uchar daddr,uchar addr,uchar dat);
uchar IIC_Read_One_Byte(uchar daddr,uchar addr);	 

uchar Device_Read_Byte(uchar DevAdd,uchar add);
void Device_Write_Byte(uchar DevAdd,uchar add,uchar dat);
 
#endif
















