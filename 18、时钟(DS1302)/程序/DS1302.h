#ifndef __DS1302_H__
#define __DS1302_H__

#include<reg51.h>     //������Ƭ���Ĵ�����ͷ�ļ�
#include<intrins.h>   //����_nop_()���������ͷ�ļ�
#define uchar unsigned char 


void Write1302(uchar dat);
void WriteSet1302(uchar Cmd,uchar dat);
uchar Read1302(void);
uchar  ReadSet1302(uchar Cmd);
void Init_DS1302(void);

#endif 