/********************************************************

					������ʵ��
				
		LCD1602��ʾ����						
		���ӷ�����LCD1602ֱ�Ӳ���1602�Ľӿ�
			  
********************************************************/
#include<reg52.h>
//#include<delay.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

//sbit lcdrs=P2^5;
//sbit lcden=P2^3;
sbit trig=P3^6;               //����������
sbit echo=P3^3;               //����������
//P0____________DB0-DB7
uchar dis[]="Disp_HC-SR04";
uchar num[]="0123456789";
//uint distance;
uint timeh,timel,distance;
uint time;
//uchar timeH,timeL;
uchar succeed_flag = 0;
uchar flag = 0;
sbit test = P1^0;


sbit RS=P2^5;           //�Ĵ���ѡ��λ����RSλ����ΪP2.0����
sbit RW=P2^4;           //��дѡ��λ����RWλ����ΪP2.1����
sbit E=P2^3;            //ʹ���ź�λ����Eλ����ΪP2.2����
sbit BF=P0^7;           //æµ��־λ������BFλ����ΪP0.7����

void delay(uint z)
{
 uint x,y;
  for(x=z;x>0;x--)
  for(y=110;y>0;y--);
}
//
void delay20us()
 { 
    uchar a ;
    for(a=0;a<100;a++);
 }

//��ʱ1ms����
void delay1ms()
{
	uchar i,j;	
 //	for(i=0;i<10;i++)
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

void WriteString(uchar *dat)
{
	while(*dat != '\0')	
	{
		WriteData(*dat);
		dat++;
	}
}

//�������ܣ���LCD����ʾģʽ���г�ʼ������
void LcdInitiate(void)
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






void initime0()
{
	TMOD=0x01;
	TH0=0;
	TL0=0;
	EA=0;
	ET0=0;
	EX1=0;
}


void estern() interrupt 2
{
	timeh=TH0;
	timel=TL0;
//	beer();
	flag=1;						//�����жϣ���־λ����1
	EX1=0;						//ͬʱ�ض��ⲿ�жϺͶ�ʱ��
    TR0=0;
}



void diaoyong()
	{
		uint i;
		uchar temp[3];
		uchar xiaoshu;
		EA=0;
		echo=1;					//Ϊ�˼���ƽ�ĸߵͣ����ȱ�������
		trig=1;
		delay20us();
		trig=0;
		while(echo==0);			//��������ж� �����յ�������������ִ��
		flag=0;					//���յ��������־λ
		EA=1;					//ͬʱ�����ж�
		EX1=1;					//���ⲿ�ж�
		TR0=1;					//����ʱ��
		TH0=0;					//��ʱ������
		TL0=0;
		for(i=0;i<100;i++)		//�ȴ������Ľ��
		{
//			display(distance);	//��100����ʾѭ������ʱ������������ʾ��������
		}
		delay(1);				//����ʱ�����������˸
		TR0=0;					//��ʱһ��ʱ���ض϶�ʱ��
		EX1=0;					//��ʱһ��ʱ���ض��ⲿ�ж�
		if(flag==1)				//��������жϣ�˵������Ѿ����
		{
			time=timeh*256+timel;//����ⶨ���룬����ʾ
			distance=time*0.1720;
//  			display(distance);
			
			temp[0] = distance/1000 + '0';
			temp[1] = distance%1000/100 + '0';
			temp[2] = distance%100/10 + '0';
			xiaoshu = distance%10 + '0';



			WriteAddress(0x02);  //д��ʼ����ʾ��ַ,���ڵ�1�е�2�п�ʼ��ʾ
			WriteString(temp) ;
			WriteData('.');
			WriteData(xiaoshu);
//			WriteString("kjafhjk") ;

			test=1;
		}
		if(flag==0)				//���û�н����жϣ�����Ϊ0��ͬʱ����˸
		{
			distance=0;
			test=0;
		}
	}



void main()
{
	initime0();
	LcdInitiate();
	test=1;
	trig=0;
	EA=1;
	while(1)
	{
		diaoyong();
//		display(distance);
	
	}
}





