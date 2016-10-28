/************************************************************
		
		���⣺����DS1302������ʱ�ӣ���������
		
************************************************************/
#include "LCD1602.h"	 //����LCD1602ͷ�ļ�

sbit RS=P2^5;           //�Ĵ���ѡ��λ����RSλ����ΪP2.0����
sbit RW=P2^4;           //��дѡ��λ����RWλ����ΪP2.1����
sbit E=P2^3;            //ʹ���ź�λ����Eλ����ΪP2.2����
sbit BF=P0^7;           //æµ��־λ������BFλ����ΪP0.7����
//��ʱ1ms����
void delay1ms()
{
	uchar i,j;	
 	for(i=0;i<10;i++)
  	for(j=0;j<33;j++);	 
}
//��ʱnms����
void delaynms(uchar n)
{
	uchar i;
	for(i=0;i<n;i++)
   	delay1ms();
}

//�������ܣ��ж�Һ��ģ���æµ״̬������ֵ��result��result=1��æµ;result=0����æ
bit BusyTest(void)
{
    bit result;
	RS=0;       //���ݹ涨��RSΪ�͵�ƽ��RWΪ�ߵ�ƽʱ�����Զ�״̬
    RW=1;
    E=1;        //E=1���������д
    _nop_();   //�ղ���
    _nop_();
    _nop_(); 
    _nop_();   //�ղ����ĸ��������ڣ���Ӳ����Ӧʱ��	
    result=BF;  //��æµ��־��ƽ����result
    E=0;         //��E�ָ��͵�ƽ
    return result;
}

//�������ܣ���ģʽ����ָ�����ʾ��ַд��Һ��ģ��
void WriteInstruction (uchar dictate)
{   
    while(BusyTest()==1);  
	 RS=0;                 
	 RW=0;   
	 E=0;                  
                           
	 _nop_();
	 _nop_();              
	 P0=dictate;           
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();              
	 E=1;                  
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();              
	  E=0;                 
 }

//�������ܣ�ָ���ַ���ʾ��ʵ�ʵ�ַ
void WriteAddress(uchar x)
{
    WriteInstruction(x|0x80); //��ʾλ�õ�ȷ�������涨Ϊ"80H+��ַ��x"
}

//�������ܣ�������(�ַ��ı�׼ASCII��)д��Һ��ģ��
void WriteData(uchar y)
{
    while(BusyTest()==1);  
	  RS=1;           
	  RW=0;
	  E=0;         
                   
	  P0=y;        
	  _nop_();
	  _nop_();
 	  _nop_();
     _nop_();      
	  E=1;         
	  _nop_();
	  _nop_();
	  _nop_();
	 _nop_();      
	 E=0;          
}

void WriteString(uchar *a)
{
	while(*a != '\0')	
	{
		WriteData(*a);
		a++;
	}
}

//�������ܣ���LCD����ʾģʽ���г�ʼ������
void Lcd1602_Init(void)
{
    delaynms(15);              
    WriteInstruction(0x38);    
	delaynms(5);               
    WriteInstruction(0x38);
	delaynms(5);               
	WriteInstruction(0x38);    
	delaynms(5);               
	WriteInstruction(0x0c);    
	delaynms(5);               
	WriteInstruction(0x06);    
	delaynms(5);               
	WriteInstruction(0x01);    
	delaynms(5);             

 }
