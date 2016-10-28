/********************************************************

					LCD12864实验
				
		LCD12864显示"LCD12864 Testing"和"By Beyonday"						
		连接方法：LCD12864直接插在12864的接口
			  
********************************************************/
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
/************* 12864LCD引脚定义 *************/
#define LCD_data  P0       //数据口
sbit LCD_RS  =  P2^5;      //寄存器选择输入 
sbit LCD_RW  =  P2^4;      //液晶读/写控制
sbit LCD_EN  =  P2^3;      //液晶使能控制
sbit LCD_PSB =  P3^5;      //串/并方式控制
sbit LCD_RST =  P3^7;      //液晶复位端口


#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
/*********************************************************/
uchar code  DIS1[] = {"                "};
uchar code  DIS2[] = {"LCD12864 Testing"};
uchar code  DIS3[] = {"     By Beyonday"};
uchar code  DIS4[] = {"                "};
/*********************************************************/


/*********************************************************
                                                                
       		延时函数                                                       
                                                                
**********************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<150;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}	
/**********************************************************
                                                                 
  			延时函数                                                       
                                                                 
***********************************************************/
void delay1(int ms)
{
    while(ms--)
	{
      uchar y;
	  for(y=0;y<100;y++) ; 
	}
}			
/**********************************************************
                                                                 
	检查LCD忙状态                                                    
	lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      
                                                                 
***********************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
/**********************************************************
                                                                 
	写指令数据到LCD                                                  
	RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             
                                                                 
***********************************************************/
void lcd_wcmd(uchar cmd)
{                          
	while(lcd_busy());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	_nop_();
	_nop_(); 
	P0 = cmd;
	delayNOP();
	LCD_EN = 1;
	delayNOP();
	LCD_EN = 0;  
}
/*************************************************************
                                                            
	写显示数据到LCD                                             
	RS=H，RW=L，E=高脉冲，D0-D7=数据。                          
                                                            
************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/************************************************************
                                                            
	LCD初始化设定                                             
                                                            
************************************************************/
void lcd_init()
{ 
    LCD_PSB = 1;         //并口方式
    
	LCD_RST = 0;		 //液晶复位
    delay(3);                   
    LCD_RST = 1;      
    delay(3);
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}
/********************************************************
                                                       
 	设定显示位置                                          
                                                       
********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==1)
     {X=0x80;}
   else if (X==2)
     {X=0x90;}
   else if (X==3)
     {X=0x88;}
   else if (X==4)
     {X=0x98;}
   pos = X+Y ; 
 
   lcd_wcmd(pos);     //显示地址
}
/*******************************************************
                                                       
 	闪烁函数                                              
                                                       
*******************************************************/
void lcdflag() 
{
   lcd_wcmd(0x08);   
   delay(400);
   lcd_wcmd(0x0c);   
   delay(400);
   lcd_wcmd(0x08);   
   delay(400);
   lcd_wcmd(0x0c);   
   delay(400);
   lcd_wcmd(0x08);   
   delay(200); 
   lcd_wcmd(0x0c);   
   delay(5);
   lcd_wcmd(0x01);   
   delay(5);
}
/*******************************************************
                                                       
 	图形显示                                              
                                                       
*******************************************************/
void photodisplay(uchar *bmp)	
{ 
  uchar i,j;

  lcd_wcmd(0x34);        //写数据时,关闭图形显示

  for(i=0;i<32;i++)
  {
    lcd_wcmd(0x80+i);    //先写入水平坐标值
    lcd_wcmd(0x80);      //写入垂直坐标值
    for(j=0;j<16;j++)   //再写入两个8位元的数据    
    lcd_wdat(*bmp++);     
    delay1(1);
  }

  for(i=0;i<32;i++)
  { 
    lcd_wcmd(0x80+i);
    lcd_wcmd(0x88);
    for(j=0;j<16;j++)         
	lcd_wdat(*bmp++);    
	delay1(1);
  }
  lcd_wcmd(0x36);       //写完数据,开图形显示 
}
/*****************************************************
                                                     
 	清屏函数                                            
                                                     
******************************************************/
void  clr_screen()
{
   lcd_wcmd(0x34);      //扩充指令操作
   delay(5);    
   lcd_wcmd(0x30);      //基本指令操作
   delay(5); 
   lcd_wcmd(0x01);      //清屏 
   delay(5);     
}
/*******************************************************
	
	 显示字符表代码

********************************************************/
void  bytecode()
{
   uchar  s;
   clr_screen();          //清屏    
   lcd_wcmd(0x80);        //设置显示位置为第一行  
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x30+s); 
   }
   lcd_wcmd(0x90);        //设置显示位置为第二行 
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x40+s); 
   }
   lcd_wcmd(0x88);        //设置显示位置为第三行  
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x50+s); 
   }
   lcd_wcmd(0x98);       //设置显示位置为第四行   
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x60+s); 
   }
}
/*********************************************************
*                                                        *
* 主函数                                                 *
*                                                        *
*********************************************************/
void main()
{
   uchar i;
   delay(100);                 //上电，等待稳定
   lcd_init();                 //初始化LCD
   while(1)
   {
     lcd_pos(1,0);             //设置显示位置为第一行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS1[i]);
       delay(30);
     }

     lcd_pos(2,0);             //设置显示位置为第二行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS2[i]);
       delay(30);
     }
     lcd_pos(3,0);             //设置显示位置为第三行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS3[i]);
       delay(30);
     }
     lcd_pos(4,0);             //设置显示位置为第四行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS4[i]);
       delay(30);
     }
     delay(1000);
     lcdflag();
     clr_screen();             //清屏        

     bytecode();               //显示字符表代码
     delay(2000);
     clr_screen();  
   }
}
/*********************************************************/




