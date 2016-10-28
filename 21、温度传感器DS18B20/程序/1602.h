#ifndef __LCD1602_H__
#define __LCD1602_H__

#include<reg52.h>     //������Ƭ���Ĵ�����ͷ�ļ�
#include<intrins.h>   //����_nop_()���������ͷ�ļ�
#define uchar unsigned char 

void delaynms(uchar n);
void WriteInstruction (uchar dictate);
void WriteAddress(uchar x);
void WriteData(uchar y);
void WriteString(uchar *dat);
void LcdInitiate(void);

#endif 
