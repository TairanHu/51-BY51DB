#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg52.h>     //包含单片机寄存器的头文件
#include<intrins.h>   //包含_nop_()函数定义的头文件
#define uchar unsigned char
#define uint unsigned int

void TempDelay (uchar us);	//18b20的函数声明
void Init18b20 (void);
void WriteByte (uchar wr);  //单字节写入
void read_bytes (uchar j);
uchar CRC (uchar j);
void GemTemp (void);
void TemperatuerResult(void);
void GetTemp();

extern uint Temperature;









#endif