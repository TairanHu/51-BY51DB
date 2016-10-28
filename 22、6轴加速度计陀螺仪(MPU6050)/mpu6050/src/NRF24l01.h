#ifndef __24L01_H
#define __24L01_H	 		  
#include "includes.h" 									   	   

void NRF24L01_Test(void);

void NRF24L01_Init(void);//��ʼ��
void RX_Mode(void);//����Ϊ����ģʽ
void TX_Mode(void);//����Ϊ����ģʽ

uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar u8s);//д������
uchar NRF24L01_Read_Buf(uchar reg, uchar *pBuf, uchar u8s);//��������		  
uchar NRF24L01_Read_Reg(uchar reg);			//���Ĵ���
uchar NRF24L01_Write_Reg(uchar reg, uchar value);//д�Ĵ���
uchar NRF24L01_Check(void);//���24L01�Ƿ����
uchar NRF24L01_TxPacket(uchar *txbuf);//����һ����������
uchar NRF24L01_RxPacket(uchar *rxbuf);//����һ����������

#endif











