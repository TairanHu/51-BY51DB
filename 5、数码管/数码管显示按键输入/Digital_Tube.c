/**************************************************

 �������������������ʾ
 �������������ĸ��ֱ��1,10,100,1000
 �����ĸ����Ǽ�

 ���߷�������Ƭ��P0�ڽ�DIGJP��P1�ڽ�U11JP1


***************************************************/

#include <reg52.h>

#define uchar unsigned char

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
uchar code Disp_Tab[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  //�������

//�˱�Ϊ8�������λѡ����, ��������� 1-8��  - 
uchar code Disp_Bit[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdF, 0xbF, 0x7F};    //λѡ����   ���ķ�������

uchar LED_Out[8] = {0x00};
uchar KeyPort;

void display();

/***********************************************

	   ��ʱ����    ��ʱʱ�����Ϊn����

************************************************/
void delay_nms(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 110; j++) ;
	}	
}

/***********************************************

	  ������

***********************************************/
void main()
{
//	uchar Bit;               //�������λ

	int Num_High , Num_Low;	 //�������ֵĸ���λ�͵���λ
	
	Num_High = 0;
	Num_Low = 0;

	while(1)
	{
		

		if(Num_Low >= 10000)
		{
			Num_High++;
			Num_Low %= 1000;
		}

		LED_Out[0] = Num_Low%10;		//ȡ�����ָ�λ
		LED_Out[1] = Num_Low/10%10;     //ȡ������ʮλ
		LED_Out[2] = Num_Low/100%10;    //ȡ�����ְ�λ
		LED_Out[3] = Num_Low/1000%10;   //ȡ������ǧλ
                                        
		LED_Out[4] = Num_High%10;       //ȡ��������λ
		LED_Out[5] = Num_High/10%10;    //ȡ������ʮ��λ
		LED_Out[6] = Num_High/100%10;   //ȡ�����ְ���λ
		LED_Out[7] = Num_High/1000%10;  //ȡ������ǧ��λ

		KeyPort = P2;
		
		while(P2 != 0xff)
		{
			display();
		}		

		switch(KeyPort)		//������ĸ�����������
		{
			case 0xfe: Num_Low += 1;    break;
			case 0xfd: Num_Low += 10;   break;
			case 0xfb: Num_Low += 100;  break;
			case 0xf7: Num_Low += 1000; break;
			
			case 0xef: Num_Low -= 1;    break;
			case 0xdf: Num_Low -= 10;   break;
			case 0xbf: Num_Low -= 100;  break;
			case 0x7f: Num_Low -= 1000; break; 
		}
		
		display();		
//		//�ӵ�һλ����ܿ�ʼ�������ʾ
//		for(Bit = 0; Bit < 8; Bit++)	  
//		{
//			P0 = Disp_Bit[Bit];
//			P1 = Disp_Tab[LED_Out[8-Bit]];
//			delay_nms(1);
//		}
	}
}


void display()
{
	uchar Bit;               //�������λ

	//�ӵ�һλ����ܿ�ʼ�������ʾ
	for(Bit = 0; Bit < 8; Bit++)	  
	{
		P0 = Disp_Bit[Bit];
		P1 = Disp_Tab[LED_Out[7-Bit]];
		delay_nms(1);
	}
}



