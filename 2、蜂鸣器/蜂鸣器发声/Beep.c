/********************************************************

						����������ʵ��
						
		���ӷ��������������Ա�����������ñ��·
		

********************************************************/


#include <reg52.h>

sbit BEEP = P1^0;		//���������ΪP1^0��
					
void main()			
{					
	while(1)		
	{				
		BEEP = 1;	//����������	
	}
}

