#ifndef _MEMBER_H
#define _MEMBER_H
#include "includes.h"

void Delay_ms(uint z);

extern uchar Timer0Count;

sbit KEY1=P0^0;
sbit KEY2=P0^1;

sbit beef=P1^0;
sbit relay=P1^1;



/***************************OLED***********************************/
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



/*****************************ledarray************************************/

extern code uchar ledarray_num[][8];

#define LEDARRAY_SCAN(x) P0=1<<x
#define LEDARRAY_DATA P2

/**************************************OLED****************************************/

extern code uchar f6x8[][6];
extern code uchar f8x16[];



#endif
