/*******************************************************

				�������ʵ��
				
 		��Ƭ���ɼ�������̵���Ϣ�����������ʾ״̬

		��Ҫ�ú����������ɨ��ԭ��

********************************************************/

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

#define keyport (P1)
#define keystate0 0		//����ȷ��״̬
#define keystate1 1		//�����޶���״̬
char keystate=1;	//����״̬��ʼ��Ϊ�����޶���״̬
uchar keynum=0;

uchar code table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void delayms(uint x)	//1ms
{
	uint y,z;
	for(y=x;y>0;y--)
		for(z=111;z>0;z--);
}


void keyscan()
{
	uchar temp1,temp2,column,row;
	switch(keystate)		
	{
		case keystate0:	//keystate0����������ȷ��״̬����һ״̬Ϊkeystate1(�����޶���״̬)
			keyport=0x0f;
			temp1=keyport;
			keyport=0xf0;
			temp2=keyport;			
			if((temp1|temp2)!=0xff)
			{
				temp1|=temp2;		//1110 1110   //1101 1110
				if(!(temp1&0x80)) //1000 0000
					row=3;
				else 
					if(!(temp1&0x40))  //0100 0000
						row=2;	
					else
						if(!(temp1&0x20))
							row=1;
						else
							if(!(temp1&0x10))
								row=0;
				if(!(temp1&0x08))	 //0000 1000
					column=3;
				else 
					if(!(temp1&0x04)) //0000 0100
						column=2;	
					else
						if(!(temp1&0x02))
							column=1;
						else
							if(!(temp1&0x01))	// 1110 1110
								column=0;
				keynum=column*4+row;
				while(!(keyport==0x0f|keyport==0xf0));
				keystate=keystate1;
				break;				
				
			}
			else
				keystate=keystate1;
			break;
		case keystate1:	//keystate1�������޶���״̬����һ״̬Ϊkeystate0(�����޶���״̬)
			keyport=0x0f;
			temp1=keyport;
			keyport=0xf0;
			temp2=keyport;			
			if((temp1|temp2)!=0xff)
			{
				keystate=keystate0;
			}
			else
				keystate=keystate1;
			break;
	}
}

void main()
{
	while(1)
	{
		keyscan();				//����ɨ��
//		P0 = ~keynum;
		P0 = table[keynum];		//��ʾ����״̬
	}
}