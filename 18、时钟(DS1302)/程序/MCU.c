/************************************************************
		
		����DS1302������ʱ�ӣ���������

		д��ʱ�䣬������LCD1602��ʾʱ��	
		ʵʱʱ���Ե�����������ñ��·	
************************************************************/
#include "DS1302.h"     //������Ƭ���Ĵ�����ͷ�ļ�
#include "LCD1602.h"    //����LCD1602ͷ�ļ�
extern uchar code num[10];
//��ʾ��
uchar second,minute,hour,day,month,year;      
uchar ReadValue;     //�����1302��ȡ������
uchar pic=0,num1=0,num2=0;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f};

void DisplaySecond(uchar x)
{
 	uchar i,j;     //j,k,l�ֱ𴢴����ֵ�ʮλ�͸�λ
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x49);    
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);           
}

//��ʾ��
void DisplayMinute(uchar x)
{
 	uchar i,j;     
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x46);    
	WriteData(num[i]);  
	WriteData(num[j]);   
	delaynms(50);           
}

//��ʾʱ
void DisplayHour(uchar x)
{
 	uchar i,j;     //j,k,l�ֱ𴢴��¶ȵİ�λ��ʮλ�͸�λ
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x43);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);           
}

//��ʾ��
void DisplayDay(uchar x)
{
 uchar i,j;     //j,k,l�ֱ𴢴��¶ȵİ�λ��ʮλ�͸�λ
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x0a);    
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
}

//��ʾ��
void DisplayMonth(uchar x)
{
 	uchar i,j;     //j,k,l�ֱ𴢴��¶ȵİ�λ��ʮλ�͸�λ
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x07);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
 }

//��ʾ��
void DisplayYear(uchar x)
{
 	uchar i,j;     //j,k,l�ֱ𴢴��¶ȵİ�λ��ʮλ�͸�λ
	i=x/10;//ȡʮλ
	j=x%10;//ȡ��λ     
	WriteAddress(0x04);   
	WriteData(num[i]);    
	WriteData(num[j]);    
	delaynms(50);         
}

//������
void main(void)
{
	
	
	LcdInitiate();       //��Һ����ʼ��
	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  //дDate����ʾ��ַ,���ڵ�1�е�2�п�ʼ��ʾ
	WriteData('2');      //���ַ�����д��LCD
	WriteData('0');      //���ַ�����д��LCD
	WriteAddress(0x06);  //д���·ָ�������ʾ��ַ�� ��ʾ�ڵ�1�е�9��
	WriteData('-');      //���ַ�����д��LCD
	WriteAddress(0x09);  //д���շָ�������ʾ��ַ�� ��ʾ�ڵ�1�е�12��
	WriteData('-');      //���ַ�����д��LCD
	WriteAddress(0x45);  //дСʱ����ӷָ�������ʾ��ַ�� ��ʾ�ڵ�2�е�6��
	WriteData(':');      //���ַ�����д��LCD
	WriteAddress(0x0d);  //д��������ָ�������ʾ��ַ�� ��ʾ�ڵ�2�е�9��
	WriteData('^');      //���ַ�����д��LCD
	WriteData('_');      //���ַ�����д��LCD
	WriteData('^');      //���ַ�����д��LCD
	WriteAddress(0x48);  //д��������ָ�������ʾ��ַ�� ��ʾ�ڵ�2�е�9��
	WriteData(':');      //���ַ�����д��LCD  
	WriteAddress(0x4d);  //д��������ָ�������ʾ��ַ�� ��ʾ�ڵ�2�е�9��
	WriteData('^');      //���ַ�����д��LCD
	WriteData('o');      //���ַ�����д��LCD
	WriteData('^');      //���ַ�����д��LCD
	Init_DS1302();       //��1302��ʼ��
	

   	
	while(1)
	{
		

	{
		
	    ReadValue = ReadSet1302(0x81);   //����Ĵ���������
		second=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);//����������ת��
		DisplaySecond(second);          //��ʾ��
		
		 ReadValue = ReadSet1302(0x83);  //�ӷּĴ�����
		minute=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //����������ת��
		DisplayMinute(minute);	       //��ʾ��
		 ReadValue = ReadSet1302(0x85);  //�ӷּĴ�����
		hour=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //����������ת��
		DisplayHour(hour);	             //��ʾСʱ
		ReadValue = ReadSet1302(0x87);  //�ӷּĴ�����
		day=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //����������ת��
		DisplayDay(day);                //��ʾ��
		ReadValue = ReadSet1302(0x89);  //�ӷּĴ�����
		month=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //����������ת��
		DisplayMonth(month);            //��ʾ��
		ReadValue = ReadSet1302(0x8d);  //�ӷּĴ�����
		year=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); //����������ת��
		DisplayYear(year);              //��ʾ��  
	}
	}
}


