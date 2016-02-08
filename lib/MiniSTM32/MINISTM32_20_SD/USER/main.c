#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
#include "mmc_sd.h"
//Mini STM32开发板范例代码20
//SD卡 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
						
u8 buf[512];//SD卡数据缓存区
 
 int main(void)
 {  	
 	u32 sector_size;
	u8 t=0;	
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	POINT_COLOR=RED;//设置字体为红色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"SD Card TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");				 
	while(SD_Initialize()!=0)//检测不到SD卡
	{
		LCD_ShowString(60,130,"SD Card Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check!      ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
	//检测SD卡成功 											    
	LCD_ShowString(60,130,"SD Card Checked OK ");
	sector_size=SD_GetSectorCount();
	printf(" SD Sector Size:%x\n",sector_size);
	LCD_ShowString(60,150,"SD Card Size:    Mb");
	LCD_ShowNum(164,150,sector_size>>12,4,16);
	while(1)
	{
		if(t==30)//每6s钟执行一次
		{
			if(SD_ReadDisk(buf,0,1)==0)//读取MBR扇区
			{	
				LCD_ShowString(60,170,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\n");
				for(sector_size=0;sector_size<512;sector_size++)printf("%x ",buf[sector_size]);//打印MBR扇区数据    	   
				printf("\nDATA ENDED\n");
				LCD_ShowString(60,170,"USART1 Send Data Over!");
			}
			t=0;
		}   
		t++;
		delay_ms(200);
		LED0=!LED0;
	}
}

