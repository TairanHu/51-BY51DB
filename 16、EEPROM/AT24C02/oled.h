#ifndef OLED_H
#define OLED_H
#include <reg52.h>

#define uchar unsigned char

sbit LCD_SCL=P2^5;
sbit LCD_SDE=P2^4;
sbit LCD_RST=P2^7;
sbit LCD_DC=P2^6;
sbit LCD_CS=P2^3;

#define X_width 128
#define Y_width 64

extern code uchar f6x8[][6] ;
extern code uchar f8x16[];
extern code uchar logo[896];


void OLED_Test(void);
void LCD_Init(void);
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
