/********************************************************

						LED移位实验
						
		连接方法：P1口排针和LED排针用排线连接起来
		

********************************************************/



#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char


void delay();


/*******************************************************

	采用C语言自带左移(<<)右移(>>)运算符实现LED移动

*******************************************************/
//void main()	   
//{
//	int count = 0;
//	P1 = 0xff;			//单片机P1口置为高电平，LED熄灭
//	while(1)
//	{
//		for(count = 0; count <= 8; count++)		//循环8次
//		{
//			 P1 = P1 << count;		//对P1口数据进行左移操作，控制LED
//			 delay();				//延时
//		}
//		P1 = 0xff;					//熄灭LED
//
//		for(count = 0; count <= 8; count++)		//循环8次
//		{
//			 P1 = P1 >> count;		//对P1口数据进行右移操作，控制LED
//			 delay();				//延时
//		}
//		P1 = 0xff;					//熄灭LED
//				
//	}
//
//}


/********************************************
		利用C51库中自带函数实现移位
				左移 _crol_
				右移 _cror_
********************************************/
void main()
{
	uchar led = 0xfe;
	uchar count;
	while(1)
	{
		count = 7;
		while(count--)				//循环
		{
			P1 = led;				//将数据赋值给P1，控制LED
			delay();				//延时
			led = _crol_(led, 1);	//左移一位
		}
		
		count = 7;
		while(count--)				//循环
		{
			P1 = led;				//将数据赋值给P1，控制LED
			delay();				//延时
			led = _cror_(led, 1);	//右移一位
		}
						
	}

}

void delay()						//延时函数
{
	int i,j;
	for(i = 0; i < 100; i++)
	{
		for(j = 0; j < 110; j++) ;
	}
}


