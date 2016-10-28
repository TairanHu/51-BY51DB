#ifndef _1602_H
#define _1602_H
#include "includes.h"

void LCD1602_Test(void);
void LCD1602_Init(void);
void LCD1602_WriteCom(uchar com);
void LCD1602_WriteData(uchar date);
void LCD1602_ShowString(uchar x,uchar y,uchar *ch);
void LCD1602_ShowNum(uchar x,uchar y,uint num,uchar len);
bit LCD1602_LcdBusy(void);
uint MyPow(uint m,uint n);//m^n

#endif