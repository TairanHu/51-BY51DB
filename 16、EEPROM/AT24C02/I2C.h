

#ifndef	_I2C_H
#define _I2C_H

#define uchar unsigned char

extern bit ack;

//�����ߺ���
extern void Start_I2c();

//�������ߺ���  
extern void Stop_I2c();

//Ӧ���Ӻ���
extern void Ack_I2c(bit a);

//�ֽ����ݷ��ͺ���
extern void  SendByte(unsigned char  c);

//���ӵ�ַ���ֽ����ݺ���               
extern unsigned char RcvByte();

#endif