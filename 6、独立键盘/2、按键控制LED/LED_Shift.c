/********************************************************

					��������LEDʵ��
						
		���ӷ�����P1��������LED������������������
				  P0�������밴��BTJP��������������	
		

********************************************************/


#include <reg52.h>
#include <intrins.h>

sbit BUTTON1 = P0^0;	   //����P0.0Ϊ1�Ű����ӿ�
sbit BUTTON2 = P0^1;	   //����P0.1Ϊ2�Ű����ӿ�

void delay()
{
	int i,j;
	for(i = 0; i < 100; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}

//void main()
//{
//	unsigned char led = 0xfe;
//	P1 = led;
//	while(1)
//	{
//		if(BUTTON1 == 0)
//		{
//			delay();
//			if(BUTTON1 == 0)
//			{
//				led = _crol_(led, 1);		
//			}
//		}
//		else if(BUTTON2 == 0)
//		{
//			delay();
//			if(BUTTON2 == 0)
//			{
//				led = _cror_(led, 1);
//			}
//		}
//		
//		P1 = led;	
//	}
//}



void main()
{
	unsigned char led = 0xfe;
	P1 = led;		   					 //��ʼ��P1Ϊ0xfe�����һ���˿�����͵�ƽ����������ߵ�ƽ������һ��LED����
	while(1)
	{
		if(BUTTON1 == 0)	             //�����һ���������£�LED������һλ
		{
			delay();
			while(BUTTON1 == 0);

			delay();
//			if(BUTTON1 == 0)
			{
				led = _crol_(led, 1);		
			}
		}
		else if(BUTTON2 == 0)			  //����ڶ����������£�LED ����һλ
		{
			delay();
			while(BUTTON2 == 0)	;
			delay();
//			if(BUTTON2 == 0)
			{
				led = _cror_(led, 1);
			}
		}
		
		P1 = led;	
	}
}
