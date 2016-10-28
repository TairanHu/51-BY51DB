#include "uart.h"

void Uart_Init(short bound)
{
	EA=1;//�����ж�
	
	SCON=0x50;//���ù�����ʽΪ8λ�����ʿɱ�
	PCON=0x80;//�����ʼӱ�
	TMOD=0x20;//��ʱ��1����ģʽ8λ�Զ���װ
	TH1=TL1=256-(57600/bound);//�����=Sysclk/12/(256-TH1) ������=��2/32��x �����
	
	ES=1;//�������ж�
	//ET1=1;//����ʱ���ж�
	TR1=1;//������ʱ��
	
	
	//STC12C��Ƭ��
	//���������ʷ�����
	//BRT=256-(750000/bound);				   //�����=Sysclk/(256-BRT) ������=��2/32��x �����	//12M 750000
	//SCON=0x50;//���ù�����ʽΪ8λ�����ʿɱ�
	//PCON=0x80;//�����ʼӱ�
	//AUXR=0x15;//ʹ�ö�����������������ÿһ��ʱ�Ӽ���һ��
}

void Uart(void) interrupt 4
{
	uchar temp;
	if(RI==1)
	{	
		RI=0;
		temp=SBUF;
		UartSentChar(temp);
		//UartSendStr("test");
		
	}
}


void UartSentChar(uchar ch)
{
	SBUF=ch; //��������
	while(!TI);//�ȴ��������
	TI=0;
}

void UartSendStr(uchar *ch)
{
	while(*ch)
	{
		UartSentChar(*ch);
		ch++;
	}	
}

void Uart_SendNum(int num)		 //���ַ��ͺ���
{ 
  uchar ch[8] = {0};
  
  if(num < 0)
  {
    ch[0] = '-';
    num = -num;
  }
  else
    ch[0] = ' ';
  
  ch[1] = num / 100000 + '0';
  ch[2] = num % 100000 / 10000 + '0';
  ch[3] = num % 10000 /1000 + '0';
  ch[4]	= num % 1000 / 100 + '0';
  ch[5] = num % 100 / 10 + '0';
  ch[6]	= num % 10 + '0';

  UartSendStr(ch);
  UartSendStr("  ");
 //for(i=0;i<7;i++)
//	UartSendChar(ch[i]);
}

