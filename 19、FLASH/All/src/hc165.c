#include "hc165.h"


void HC165_Test(uchar testdat)
{
	uchar temp;
	HC_DIN=testdat;
	temp=HC165_GetData();
	
	if(temp==HC_DIN)
	{
		Show_f8x16str(0,0,"HC165 Test Pass!");
		Show_f8x16str(0,2,"Rev Data is:");
		Show_Num_f8x16(97,2,temp,3);
	}
	else
	{
		Show_f8x16str(0,0,"HC165 Test fail!");
		Show_f8x16str(0,2,"Rev Data is:");
		Show_Num_f8x16(97,2,temp,3);
	}
	
//	if(temp==HC_DIN)
//	{
//		LCD1602_ShowString(1,1,"HC165 Test Pass!");
//		LCD1602_ShowString(1,2,"Rev Data is:");
//		LCD1602_ShowNum(13,2,temp,3);
//	}
//	else 
//	{
//		LCD1602_ShowString(1,1,"HC165 Test Fail!");
//		LCD1602_ShowString(1,2,"Rev Data is:");
//		LCD1602_ShowNum(13,2,temp,3);
//	}
	
}
uchar HC165_GetData(void)
{
	uchar i,result=0;
	HC165_CLK=1;
	HC165_PL=0;//读取并口数据
	HC165_PL=1;
	
	if(HC165_SO)result|=1;
	
	for(i=0;i<7;i++)
	{
		HC165_CLK=0;
		HC165_CLK=1;//时钟脉冲
		
		result=result<<1;
		if(HC165_SO)result|=1;	
	}
	return result;
}