#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "mmc_sd.h"
#include "ff.h"
#include "integer.h"
#include "diskio.h"
#include "text.h"
#include "24cxx.h"
#include "fontupd.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "touch.h"
//Mini STM32开发板范例代码26
//触控USB鼠标 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com


//装载画图的界面
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(216,0,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}
int main(void)
{	
	u8 key;
	u8 i=0;
	u8 tpx=0;	  
	s8 x0;		 //发送到电脑端的坐标值
	s8 y0;
	short xlast; //最后一次按下的坐标值
	short ylast;			  
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	//USB配置
	USB_Interrupts_Config();    
	Set_USBClock();   
	USB_Init();	   
 	POINT_COLOR=RED;//设置字体为蓝色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"USB TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/2");	
	LCD_ShowString(60,130,"Press KEY0 to Adjust");	
	Touch_Init();
	delay_ms(1500);
	Load_Drow_Dialog();	     
	while(1)
	{	
		key=KEY_Scan();
		tpx=AI_Read_TP();//得到触点的状态
		if(tpx)//触摸屏被按下						  
		{											   
			xlast=Pen_Point.X0;
			ylast=Pen_Point.Y0;
			while(1)
			{
				tpx=AI_Read_TP();
				if(tpx==0)break;//触点松开了							 
				if(Pen_Point.X0>216&&Pen_Point.Y0<16)Load_Drow_Dialog();//清除
				else Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);//画图  
				if((Pen_Point.X0!=xlast||Pen_Point.Y0!=ylast)&&(bDeviceState==CONFIGURED)&&tpx==1)
				{
					x0=(xlast-Pen_Point.X0)*3;//上次坐标值与得到的坐标值之差,扩大3倍
					y0=(ylast-Pen_Point.Y0)*3;
					xlast=Pen_Point.X0;		  //记录本次的坐标值
					ylast=Pen_Point.Y0;
					Joystick_Send(0,-x0,-y0,0); //发送数据到电脑  
					delay_ms(10);	   
				}else if((bDeviceState==CONFIGURED)&&tpx==2)//单击
				{
					tpx=0X01;
					Joystick_Send(tpx,0,0,0);//模拟左键按下	
				} 
				delay_us(50); 
			} 
			Joystick_Send(0,0,0,0);//发送左键松开
		}else delay_ms(1);	 
		if(bDeviceState==CONFIGURED)LED1=0;//当USB配置成功了，LED1亮，否则，灭
		else LED1=1;
		if(key==1)//KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE);//清屏
		    Touch_Adjust();  //屏幕校准 
			Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i==200)
		{
			i=0;
			LED0=!LED0;
		}
	};	   		  
}   

				 

