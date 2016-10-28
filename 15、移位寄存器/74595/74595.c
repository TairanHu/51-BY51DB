/********************************************************

						74LS595��λʵ��
						
		���ӷ�����P0��������λ�Ĵ���(��ת��)U8JP1
				  P2������LED����DJP
		
********************************************************/

#include <reg52.h> 
#include <intrins.h>
#define  NOP() _nop_()  /* �����ָ�� */

//SPI IO
sbit MOSIO =P3^5;
sbit R_CLK =P3^6;
sbit S_CLK =P3^4;


void delay(unsigned int i);      //��������
void HC595SendData(unsigned char SendVal);
 

void main()
{
	unsigned char Led=0xfe;	 //1111 1110
	HC595SendData(0xff);	    //��ʼ��595ʹ��Ϊ�ߵ�ƽ ��LED����Ϩ��״̬
	   
	while(1)
	{	   	
		HC595SendData(Led);	//����595�������� ��LED�������͵�595
		Led<<=1;
		Led	= Led| 0x01;  //��λ�󣬺����λΪ�ߵ�ƽ;
		if (Led == 0xff ) Led=0xfe;  //1111 1110
		delay(300);
	 
}   
}	
/*****************************************************************************
*  ��ʱ�ӳ���															     *
*																			 *
******************************************************************************/
void delay(unsigned int i)
{
    unsigned int j;
    for(i; i > 0; i--)
        for(j = 110; j > 0; j--);
}


/*********************************************************************************************************
** ��������: HC595SendData
** ��������: ��SPI���߷�������
*********************************************************************************************************/
void HC595SendData(unsigned char SendVal)
{  
	unsigned char i;
		
	for(i=0;i<8;i++) 
	{
		if((SendVal<<i)&0x80) MOSIO=1; //set dataline high  0X80  ���λ��SendVal���Ƶ����λ �����߼�����
		else MOSIO=0;				   // ���Ϊ�� MOSIO = 1  
		 
		S_CLK=0;
		NOP();	//�������β�
		NOP();
		S_CLK=1;	
	}
	   
		
	R_CLK=0; //set dataline low
	NOP();   //�������β�
	NOP();
	R_CLK=1; //Ƭѡ

}

