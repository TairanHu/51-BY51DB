/********************************************************

				LCD1602ģ�黯ʵ��
				
		LCD1602��ʾ"LCD1602 TEST"��"By Beyonday"						
		���ӷ�����LCD1602ֱ�Ӳ���1602�Ľӿ�
			  
********************************************************/

#include <reg52.h>
#include "1602.h"    //����LCD1602ͷ�ļ�

uchar temp[] = "LCD1602 TEST";	
uchar temp1[] = "By Beyonday";

//������
void main(void)
{


	LcdInitiate();       //��Һ����ʼ��
	WriteAddress(0x00);
	WriteData(' ');
	WriteAddress(0x02);  //д��ʼ����ʾ��ַ,���ڵ�1�е�2�п�ʼ��ʾ
	WriteString(temp) ;
	WriteAddress(0x45);  //дtemp1����ʾ��ַ�� ��ʾ�ڵ�2�е�6��
	WriteString(temp1) ;

   	
	while(1)	         //��ѭ��
	{
		

	}
}


