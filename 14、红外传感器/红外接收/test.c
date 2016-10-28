/********************************************************

					�������ʵ��
				
		LED״̬��ת��ʾ�Ƿ���յ������ź�					
		���ӷ�����P1������LED
			  
********************************************************/

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

sbit IRIN = P3^2;         //���������������

uchar LED ;

void delay(uchar x);  //x*0.14MS
void delay1(int ms); 


/*******************************************************************/
void main()
{   
    IRIN=1;                    //I/O�ڳ�ʼ��
	LED = 0xaa;
	P1 = LED;

	IE = 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
	TCON = 0x01;               //������ʽΪ���帺���ش���

    while(1)
	{
	
	}


} //end main
/**********************************************************/
void IR_IN() interrupt 0 using 0
{	
	EX0 = 0;   		  //�ص��ⲿ�жϷ�ֹ�жϵ��ٴη���������������׶Σ�9ms�ĵ͵�ƽ4.5ms�ĸߵ�ƽ��
	delay(15);
	if (IRIN==1) 
	{
		EX0 =1;			  //9ms�ļ����������´��ⲿ�ж�
		return;
	} 
	                           //ȷ��IR�źų���
	while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
	{
		delay(1);
	}
	
	LED = ~LED;
	P1 = LED;
	
	EX0 = 1;
}


/**********************************************************/
void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

/**********************************************************/
void delay1(int ms)
{
	unsigned char y;
	while(ms--)
	{
		for(y = 0; y<250; y++)
		{
		   _nop_();
		   _nop_();
		   _nop_();
		   _nop_();
		}
	}
}

