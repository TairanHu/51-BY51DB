/********************************************************

						Flashʵ��
						
		��"Beyonday studio"д��оƬW25Q64��ָ��λ�ã�
		ͬʱ��ָ��λ�ö�ȡ����������OLED������ʾ
		
********************************************************/


#include "includes.h"

uchar temp;

void Serial_Port_Init()
{
	TMOD = 0x20;	   // �趨T1��ʱ���Ĺ�����ʽ2
	TH1 = 0xfd;		   // T1��ʱ��װ��ֵ
	TL1 = 0xfd;		   //
	TR1 = 1;		   // ����T1��ʱ��
	SM0 = 0;		   // �趨���ڹ�����ʽ1
	SM1 = 1;		   // 
	REN = 1;		   // �����ڽ���
	ES = 1;			   // �������ж�
	EA = 1;			   // �����ж�

}

void main(void)
{

	uchar aaa[]="Beyonday studio";
	uchar bbb[18] = {0x00};
	uchar SIZE = sizeof(aaa);

	SPI_CLK=0;

	Serial_Port_Init();
	
	OLED_Init();

//	SPI_Flash_Write_Page(aaa,8*1024*1024-450,SIZE);
//	Delay_ms(1000);
	SPI_Flash_Read(bbb,8*1024*1024-450,SIZE)  ;
	Delay_ms(1000);
	Show_f8x16str(0,0,bbb);
	
	while(1)
	{
		
	}
}

void serail() interrupt 4
{
	RI = 0;				//���жϱ�־λ
	temp = SBUF;		//���յ������ݴ���temp
//	flag = 1;			//flag��־λ��1

}


