#include "oled.h"

void OLED_Test(void)
{
	uchar i;
	for(i=0;i<4;i++)
	Show_Chinese(i*32,0,i);
	
	for(i=4;i<7;i++)
	Show_Chinese(i*32+16,4,i);
}

void Write_Com(uchar com)//写命令
{
	uchar i;
	LCD_DC=0;//写命令
	//LED_SCL=0;
	for(i=0;i<8;i++)
	{
		LCD_SCL=0;
		if((com<<i)&0x80)
			LCD_SDE=1;
		else
			LCD_SDE=0;
		LCD_SCL=1;
	}
}
void Write_Data(uchar date)//写数据
{
	uchar i;
	LCD_DC=1;//写数据
	//LED_SCL=0;
	for(i=0;i<8;i++)
	{
		LCD_SCL=0;
		if((date<<i)&0x80)
			LCD_SDE=1;
		else
			LCD_SDE=0;
		LCD_SCL=1;
	}
}
void Set_Pos(uchar x,uchar y)//设定光标起始位置
{
	Write_Com(0xb0+y);//设置起始page
	Write_Com(((x&0xf0)>>4)|0x10);//送高位起始地址
	Write_Com((x&0x0f)|0x01);//送低位起始地址 			
}
void LCD_Fill(void)//写满屏
{
	uchar y,x;	
	for(y=0;y<8;y++)
	{
		Write_Com(0xb0+y);
		Write_Com(0x01);
		Write_Com(0x10);
		for(x=0;x<X_width;x++)
			Write_Data(0xff);
	}
}
void LCD_Cls(void)//清屏
{
	uchar y,x;	
	for(y=0;y<8;y++)
	{
		Write_Com(0xb0+y);
		Write_Com(0x01);
		Write_Com(0x10); 
		for(x=0;x<X_width;x++)
			Write_Data(0);
	}
} 
void OLED_Init(void)
{
	LCD_CS=0;
	LCD_SCL=1;
	//LCD_CS=1;	//预制SLK和SS为高电平  	
	LCD_RST=0;
	Delay_ms(30);
	LCD_RST=1;
	
	//从上电到下面开始初始化要有足够的时间，即等待RC复位完毕   
  
  Write_Com(0xae);//关闭显示
  Write_Com(0x00);//---set low column address
  Write_Com(0x10);//---set high column address
  Write_Com(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)

  Write_Com(0x81);//--set contrast control register
  Write_Com(0xcf); // Set SEG Output Current Brightness

  Write_Com(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  Write_Com(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  Write_Com(0xa6);//--set normal display		 (0xa7)

  Write_Com(0xa8);//--set multiplex ratio(1 to 64)
  Write_Com(0x3f);//--1/64 duty
  Write_Com(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  Write_Com(0x00);//-not offset

  Write_Com(0xd5);//--set display clock divide ratio/oscillator frequency
  Write_Com(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec

  Write_Com(0xd9);//--set pre-charge period
  Write_Com(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock

  Write_Com(0xda);//--set com pins hardware configuration
  Write_Com(0x12);
  Write_Com(0xdb);//--set vcomh
  Write_Com(0x40);//Set VCOM Deselect Level
  Write_Com(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  Write_Com(0x02);//
  Write_Com(0x8d);//--set Charge Pump enable/disable
  Write_Com(0x14);//--set(0x10) disable
  Write_Com(0xa4);// Disable Entire Display On (0xa4/0xa5)
  Write_Com(0xa6);// Disable Inverse Display On (0xa6/a7) 
  Write_Com(0xaf);//--turn on oled panel
  LCD_Cls();  //初始清屏
  Set_Pos(0,0);
}


void Show_f6x8str(uchar x,uchar y,uchar *ch)
{
  uchar c=0,i=0,j=0;      
  while(ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126){x=0;y++;}	//换行
    Set_Pos(x,y);    
  	for(i=0;i<6;i++)     
  	  Write_Data(f6x8[c][i]);  
  	x+=6;
  	j++;
  }
}	

int My_pow(uchar m,uchar n)		//幂函数
{
	int result=1;	 
	while(n--)result*=m;    
	return result;	
}

void Show_Num_f8x16(uchar x,uchar y,uint num,uchar len)
{
	uchar temp,t,i;
	for(t=0;t<len;t++)
	{
		temp=(num/My_pow(10,len-t-1))%10;
		//if(x>120){x=0;y++;}//换行
		Set_Pos(x,y);//设定高8位起始位置
		for(i=0;i<8;i++)     
	  		Write_Data(f8x16[(temp+16)*16+i]);
		Set_Pos(x,y+1);//设定低八位起始位置
		for(i=0;i<8;i++)     
	  		Write_Data(f8x16[(temp+16)*16+8+i]);
		x+=8;
	}	
}

 
void Show_Num_f6x8(uchar x,uchar y,int num,uchar len)
{
	uchar temp,t,i;
	for(t=0;t<len;t++)
	{
		temp=(num/My_pow(10,len-t-1))%10;
		//if(x>126){x=0;y++;}//换行
		Set_Pos(x,y);//设定高8位起始位置
		for(i=0;i<6;i++)     
	  		Write_Data(f6x8[temp+16][i]);	
		x+=6;
	}	
}

void Show_f8x16str(uchar x,uchar y,uchar *ch)//显示8x16字符串
{
  uchar c=0,i=0,j=0;
        
  while(ch[j]!='\0')
  {    
    c=ch[j]-32;
    //if(x>120){x=0;y++;}//换行

    Set_Pos(x,y);//设定高8位起始位置    
  	for(i=0;i<8;i++)     
  		Write_Data(f8x16[c*16+i]);
  	Set_Pos(x,y+1);//设定低八位起始位置    
  	for(i=0;i<8;i++)     
  		Write_Data(f8x16[c*16+i+8]);  
  	x+=8;
  	j++;
  }
}


//	
void Show_Chinese(uchar x,uchar y,uchar N)
{
	uchar i;
	int adder=128*N;	    	
  	Set_Pos(x,y);
  	for(i=0;i<32;i++)
	{               
  		Write_Data(logo[adder]);
		adder++;
	}	  	   
  	Set_Pos(x,y + 1); 
	for(i=0;i<32;i++) 
	{              
  		Write_Data(logo[adder]);
		adder++;
	}	  	
	Set_Pos(x,y + 2); 
	for(i=0;i<32;i++) 
	{              
  		Write_Data(logo[adder]);
		adder++;
	}
	Set_Pos(x,y + 3); 
	for(i=0;i<32;i++) 
	{              
  		Write_Data(logo[adder]);
		adder++;
	}
} 


void Show_Picture(uchar Long,uchar *pp,uchar EN)
{
	uchar y,x,null;	

	null=(128-Long)/2;
	for(y=0;y<8;y++)
	{
		Write_Com(0xb0+y);
		Write_Com(0x01);
		Write_Com(0x10);

		for(x=0;x<null;x++)
		{
			if(EN)
			Write_Data(0xff);
			else  Write_Data(0);
		}

		for(x=null;x<Long+null;x++)
		{
			if(EN)
			Write_Data(*(pp++));

			else Write_Data(~*(pp++));
		}
		for(x=Long+null;x<128;x++)
		{
			if(EN)
			Write_Data(0xff);
			else  Write_Data(0);
		}
	}		
}


//void Show_8x16Str1(u8 x,u8 y,u8 N)
//{
//	u8 i;
//	int adder=16*N;	    	
//  	Set_Pos(x,y);
//  	for(i=0;i<8;i++)
//	{               
//  		//Write_Data(Title3[adder]);
//		adder++;
//	}	  	   
//  	Set_Pos(x,y + 1); 
//	for(i=0;i<8;i++) 
//	{              
//  		//Write_Data(Title3[adder]);
//		adder++;
//	}	
//}

//void Show_16x16Str(u8 x,u8 y,u8 N)
//{
//	u8 i;
//	int adder=32*N;	    	
//  	Set_Pos(x,y);
//  	for(i=0;i<16;i++)
//	{               
//  		//Write_Data(Title1[adder]);
//		adder++;
//	}	  	   
//  	Set_Pos(x,y + 1); 
//	for(i=0;i<16;i++) 
//	{              
//  		//Write_Data(Title1[adder]);
//		adder++;
//	}	
//}

//void Show_16x32Str(u8 x,u8 y,u8 N)
//{
//	u8 i;
//	int adder=64*N;	    	
//  	Set_Pos(x,y);
//  	for(i=0;i<16;i++)
//	{               
//  		//Write_Data(Title2[adder]);
//		adder++;
//	}	  	   
//  	Set_Pos(x,y + 1); 
//	for(i=0;i<16;i++) 
//	{              
//  		//Write_Data(Title2[adder]);
//		adder++;
//	}
//	Set_Pos(x,y + 2); 
//	for(i=0;i<16;i++) 
//	{              
//  		//Write_Data(Title2[adder]);
//		adder++;
//	}
//	Set_Pos(x,y + 3); 
//	for(i=0;i<16;i++) 
//	{              
//  		//Write_Data(Title2[adder]);
//		adder++;
//	}	
//}

//void Show_Chinese(u8 x,u8 y,u8 N)
//{
//	u8 i;
//	int adder=28*N;	    	
//  	Set_Pos(x,y);
//  	for(i=0;i<14;i++)
//	{               
//  		//Write_Data(Title[adder]);
//		adder++;
//	}	  	   
//  	Set_Pos(x,y + 1); 
//	for(i=0;i<14;i++) 
//	{              
//  		//Write_Data(Title[adder]);
//		adder++;
//	}	  	
//} 

//void Show_Title(void)
//{
//	u8 i;
//	for(i=0;i<8;i++)
//	Show_16x16Str(i*16-1,0,i);

//	for(i=0;i<8;i++)
//	Show_16x32Str(i*15+1,2,i);

//	for(i=0;i<16;i++)
//	Show_8x16Str1(i*8,6,i);
//	
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);

//	LCD_Cls();
//}



