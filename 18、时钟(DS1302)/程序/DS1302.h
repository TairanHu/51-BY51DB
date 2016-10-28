#ifndef __DS1302_H__
#define __DS1302_H__

#include<reg51.h>     //包含单片机寄存器的头文件
#include<intrins.h>   //包含_nop_()函数定义的头文件
#define uchar unsigned char 


void Write1302(uchar dat);
void WriteSet1302(uchar Cmd,uchar dat);
uchar Read1302(void);
uchar  ReadSet1302(uchar Cmd);
void Init_DS1302(void);

#endif 