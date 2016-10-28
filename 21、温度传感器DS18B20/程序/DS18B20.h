#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg52.h>     //������Ƭ���Ĵ�����ͷ�ļ�
#include<intrins.h>   //����_nop_()���������ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int

void TempDelay (uchar us);	//18b20�ĺ�������
void Init18b20 (void);
void WriteByte (uchar wr);  //���ֽ�д��
void read_bytes (uchar j);
uchar CRC (uchar j);
void GemTemp (void);
void TemperatuerResult(void);
void GetTemp();

extern uint Temperature;









#endif