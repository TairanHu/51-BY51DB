/***************************************************
	
			���ڽ��շ�������ʵ��
	������Ƭ���������ݣ���Ƭ������Է�������

****************************************************/

#include <reg52.h>

#define uchar unsigned char

uchar temp;		   //��ʱ�洢����
uchar flag;        //�����жϱ�־λ

void delay_nms(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}


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

void main()
{
	Serial_Port_Init();

	while(1)
	{
		if(flag)
		{
			SBUF = temp;			//SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
	        while(!TI);				// �������ݴ���	(TI�����жϱ�־)
			TI = 0;					// ������ݴ��ͱ�־		
			flag = 0;
		}

	}
	
}


void serail() interrupt 4
{
	RI = 0;				//���жϱ�־λ
	temp = SBUF;		//���յ������ݴ���temp
	flag = 1;			//flag��־λ��1

}




