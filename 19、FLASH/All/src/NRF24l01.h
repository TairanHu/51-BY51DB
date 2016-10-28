#ifndef __24L01_H
#define __24L01_H	 		  
#include "includes.h" 									   	   

void NRF24L01_Test(void);

void NRF24L01_Init(void);//初始化
void RX_Mode(void);//配置为接收模式
void TX_Mode(void);//配置为发送模式

uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar u8s);//写数据区
uchar NRF24L01_Read_Buf(uchar reg, uchar *pBuf, uchar u8s);//读数据区		  
uchar NRF24L01_Read_Reg(uchar reg);			//读寄存器
uchar NRF24L01_Write_Reg(uchar reg, uchar value);//写寄存器
uchar NRF24L01_Check(void);//检查24L01是否存在
uchar NRF24L01_TxPacket(uchar *txbuf);//发送一个包的数据
uchar NRF24L01_RxPacket(uchar *rxbuf);//接收一个包的数据

#endif











