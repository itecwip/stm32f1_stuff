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
//Mini STM32开发板范例代码24
//汉字显示 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com

int main(void)
{	
	u32 fontcnt;		  
	u8 i,j;
	FATFS fs;
	u8 fontx[2];//gbk码
	u8 key,t;	
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
 	SPI_Flash_Init();	//SPI FLASH初始化
	f_mount(0, &fs); //初始化必须mount
	while(font_init())
	{
UPD:	POINT_COLOR=RED;      
		LCD_Clear(WHITE);
		LCD_ShowString(60,50,"Mini STM32");	
		LCD_ShowString(60,70,"Font Updating..."); 	 
 		while(update_font())//从SD卡更新
	    {   
	       	LCD_ShowString(60,90,"FAT SYS ERROR.      ");	 
			delay_ms(200);     
			LED0=!LED0;	
		}
	}

	POINT_COLOR=RED;      
	Show_Str(60,50,"Mini STM32开发板",16,0);				    	 
	Show_Str(60,70,"GBK字库测试程序",16,0);				    	 
	Show_Str(60,90,"正点原子@ALIENTEK",16,0);				    	 
	Show_Str(60,110,"2011年1月1日",16,0);
	Show_Str(60,130,"按KEY0,更新字库",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,"内码高字节:",16,0);				    	 
	Show_Str(60,170,"内码低字节:",16,0);				    	 
	Show_Str(60,190,"对应汉字为:",16,0);			 
	Show_Str(60,210,"汉字计数器:",16,0);
	while(1) //遍历GBK子库
	{	 
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//显示内码高字节    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//显示内码低字节	 
				LCD_ShowNum(148,210,fontcnt,5,16);//显示内码低字节	 
			 	fontx[1]=j;
				Show_Font(148,190,fontx,16,0);	  
				t=200;
				while(t--)//延时,同时扫描按键
				{										  
					delay_ms(1);
					key=KEY_Scan();
				    if(key==1)
					 goto UPD;
				   
				}
				LED0=!LED0;
			}   
		}			 		   
	}

}
