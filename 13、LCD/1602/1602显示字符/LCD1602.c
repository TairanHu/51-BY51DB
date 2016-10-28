/********************************************************

					LCD1602ʵ��
				
		LCD1602��ʾ"LCD1602 TEST"��"By Beyonday"						
		���ӷ�����LCD1602ֱ�Ӳ���1602�Ľӿ�
			  
********************************************************/


#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
  
sbit RS=P2^5;           //�Ĵ���ѡ��λ����RSλ����ΪP2.0����
sbit RW=P2^4;           //��дѡ��λ����RWλ����ΪP2.1����
sbit E=P2^3;            //ʹ���ź�λ����Eλ����ΪP2.2����
sbit BF=P0^7;           //æµ��־λ������BFλ����ΪP0.7����
//��ʱ1ms����
void delay1ms()
{
	uchar i,j;	
 //	for(i=0;i<10;i++)
  	for(j=0;j<33;j++);	 
}
//��ʱnms����
void delaynms(int n)
{
	int i;
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
void LcdInitiate(void)
{
    delaynms(15);              
    WriteInstruction(0x38);    //16*2��ʾ��5*7����8λ����
	delaynms(5);               
    WriteInstruction(0x38);
	delaynms(5);               
	WriteInstruction(0x38);    
	delaynms(5);               
	WriteInstruction(0x0c);    //��ʾ�����ع��
	delaynms(5);               
	WriteInstruction(0x06);    //�ƶ����
	delaynms(5);               
	WriteInstruction(0x01);    //���LCD����ʾ����
	delaynms(5);             

 }

 void main(void)
{

	uchar temp[] = "LCD1602 TEST";	
	uchar temp1[] = "By Beyonday";

	int i = 0;

	LcdInitiate();       //��Һ����ʼ��
//	WriteAddress(0x00);
//	WriteData(' ');
//	WriteAddress(0x02);  //д��ʼ����ʾ��ַ,���ڵ�1�е�2�п�ʼ��ʾ
//	WriteString(temp) ;
//	WriteAddress(0x45);  //дtemp1����ʾ��ַ�� ��ʾ�ڵ�2�е�6��
//	WriteString(temp1) ;

   	
	while(1)	         //��ѭ��
	{
			WriteAddress(0x00);
			WriteData(' ');
			WriteAddress(0x02);  //д��ʼ����ʾ��ַ,���ڵ�1�е�2�п�ʼ��ʾ
			while(temp[i] != '\0')
			{
				WriteData(temp[i]);
				i++;
				delaynms(1000);	
			}
			i = 0;
			WriteAddress(0x45);  //дtemp1����ʾ��ַ�� ��ʾ�ڵ�2�е�6��
			while(temp1[i] != '\0')
			{
				WriteData(temp1[i]);
				i++;
				delaynms(1000);	
			}
			i = 0;
			WriteInstruction(0x01); 

			delaynms(1000);
		

	}
}



