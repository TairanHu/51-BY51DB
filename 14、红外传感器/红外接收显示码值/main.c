/********************************************************

					�������ʵ��
				
		LCD1602��ʾ���հ�����ֵ						
		���ӷ�����LCD1602ֱ�Ӳ���1602�Ľӿ�
			  
********************************************************/

#include "LCD1602.h"

#define uchar unsigned char
#define uint  unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

void delay(uchar x);  //x*0.14MS
void delay1(int ms);

sbit IRIN = P3^2;         //���������������

uchar IRCOM[7];

void main()
{
	uchar Disp1[] = "IR Display";
	uchar Disp2[] = "IR-CODE: --H";
    
    IRIN=1;                    //I/O�ڳ�ʼ��
	
    delay1(10);                 //��ʱ
    LcdInitiate();                //��ʼ��LCD             
    
	WriteAddress(0x03);    
    WriteAddress(0x03);                //������ʾλ��Ϊ��һ�еĵ�1���ַ�
	WriteString(Disp1);

    WriteAddress(0x42);                //������ʾλ��Ϊ��һ�еĵ�1���ַ�
	WriteString(Disp2);


	IE = 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
	TCON = 0x01;               //������ʽΪ���帺���ش���

   while(1)	;

} //end main



void IR_IN() interrupt 0 using 0
{
	unsigned char j,k,N=0;
	EX0 = 0;   
	delay(15);
	if (IRIN==1) 
	{ 
		EX0 =1;
		return;
	} 
	                           //ȷ��IR�źų���
	while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
	{
		delay(1);
	}
	
	for (j=0;j<4;j++)         //�ռ���������
	{ 
		for (k=0;k<8;k++)        //ÿ��������8λ
		{
			while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
			{
				delay(1);
			}
			while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
			{
				delay(1);
			}
			while (IRIN)           //����IR�ߵ�ƽʱ��
			{
				delay(1);
				N++;           
				if (N>=30)
				{ 
					EX0=1;
					return;
				}                  //0.14ms���������Զ��뿪��
			}                        //�ߵ�ƽ�������                
			IRCOM[j]=IRCOM[j] >> 1;                  //�������λ����0��
			if (N>=8) 
			{
				IRCOM[j] = IRCOM[j] | 0x80;			//�������λ����1��
			}  
			N=0;
		}//end for k
	}//end for j
	   
	if (IRCOM[2]!=~IRCOM[3])
	{ 
		EX0=1;
		return; 
	}
	
	IRCOM[5]=IRCOM[2] & 0x0F;     //ȡ����ĵ���λ
	IRCOM[6]=IRCOM[2] >> 4;       //����4�Σ�����λ��Ϊ����λ
	
	if(IRCOM[5]>9)
	{ 
		IRCOM[5]=IRCOM[5]+0x37;
	}
	else
	{
		IRCOM[5]=IRCOM[5]+0x30;
	}
	
	if(IRCOM[6]>9)
	{ 
		IRCOM[6]=IRCOM[6]+0x37;
	}
	else
	{
		IRCOM[6]=IRCOM[6]+0x30;
	}
	
	WriteAddress(0x4b);             
	WriteData(IRCOM[6]);        //��һλ����ʾ 
	WriteAddress(0x4c);             
	WriteData(IRCOM[5]);        //�ڶ�λ����ʾ
	
	EX0 = 1; 
} 

/**********************************************************/
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

