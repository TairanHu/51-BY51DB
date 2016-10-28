#ifndef OLED_H
#define OLED_H
#include "includes.h"


void OLED_Test(void);
void OLED_Init(void);
void Write_Com(uchar com);
void Write_Date(uchar date);
void Set_Pos(uchar x,uchar y);
void LCD_Cls(void);			//??
void LCD_Fill(void);		//???
void Show_f8x16str(uchar x,uchar y,uchar *ch);
void Show_f6x8str(uchar x,uchar y,uchar *ch);
void Show_Num_f8x16(uchar x,uchar y,int num,uchar len);
void Show_Num_f6x8(uchar x,uchar y,int num,uchar len);

int My_pow(uchar m,uchar n);		

void Show_Picture(uchar Long,uchar *pp,uchar EN);
void Show_Chinese(uchar x,uchar y,uchar N);


#endif 
