#ifndef __LCD1602_H__
#define __LCD1602_H__

#include<reg51.h>     //包含单片机寄存器的头文件
#include<intrins.h>   //包含_nop_()函数定义的头文件
#define uchar unsigned char 

void delaynms(uchar n);
void WriteInstruction (uchar dictate);
void WriteAddress(uchar x);
void WriteData(uchar y);
void LcdInitiate(void);
void WriteString(uchar *a);

#endif 
