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
//Mini STM32�����巶������24
//������ʾ ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com

int main(void)
{	
	u32 fontcnt;		  
	u8 i,j;
	FATFS fs;
	u8 fontx[2];//gbk��
	u8 key,t;	
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
 	SPI_Flash_Init();	//SPI FLASH��ʼ��
	f_mount(0, &fs); //��ʼ������mount
	while(font_init())
	{
UPD:	POINT_COLOR=RED;      
		LCD_Clear(WHITE);
		LCD_ShowString(60,50,"Mini STM32");	
		LCD_ShowString(60,70,"Font Updating..."); 	 
 		while(update_font())//��SD������
	    {   
	       	LCD_ShowString(60,90,"FAT SYS ERROR.      ");	 
			delay_ms(200);     
			LED0=!LED0;	
		}
	}

	POINT_COLOR=RED;      
	Show_Str(60,50,"Mini STM32������",16,0);				    	 
	Show_Str(60,70,"GBK�ֿ���Գ���",16,0);				    	 
	Show_Str(60,90,"����ԭ��@ALIENTEK",16,0);				    	 
	Show_Str(60,110,"2011��1��1��",16,0);
	Show_Str(60,130,"��KEY0,�����ֿ�",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,"������ֽ�:",16,0);				    	 
	Show_Str(60,170,"������ֽ�:",16,0);				    	 
	Show_Str(60,190,"��Ӧ����Ϊ:",16,0);			 
	Show_Str(60,210,"���ּ�����:",16,0);
	while(1) //����GBK�ӿ�
	{	 
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//��ʾ������ֽ�    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//��ʾ������ֽ�	 
				LCD_ShowNum(148,210,fontcnt,5,16);//��ʾ������ֽ�	 
			 	fontx[1]=j;
				Show_Font(148,190,fontx,16,0);	  
				t=200;
				while(t--)//��ʱ,ͬʱɨ�谴��
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
