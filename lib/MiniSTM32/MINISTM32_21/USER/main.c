#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "remote.h"
//Mini STM32开发板范例代码21
//红外遥控 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
 int main(void)
 {  	
	u8 key;
	u8 t; 
 	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();

	Remote_Init();	    //初始化红外接收
					   
 	POINT_COLOR=RED;//设置字体为红色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"REMOTE TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");
				 
	LCD_ShowString(30,130, "KEYVAL:");
	LCD_ShowString(130,130,"KEYCNT:");	  
	LCD_ShowString(30,150, "SYMBOL:");
	while(1)
	{	  
		if(Remote_Rdy)
		{
			key=Remote_Process();
			LCD_ShowNum(86,130,key,3,16);//显示键值
			LCD_ShowNum(186,130,Remote_Cnt,3,16);//显示按键次数		  
			switch(key)
			{
				case 0:
					LCD_ShowString(86,150, "ERROR");
					break;
				case 162: 
					LCD_ShowString(86,150, "POWER");	  
					break;
				case 98:
					LCD_ShowString(86,150, "UP    ");
					break;
				case 2:
					LCD_ShowString(86,150, "PLAY  ");
					break;
				case 226:
					LCD_ShowString(86,150, "ALIEN ");
					break;
				case 194:
					LCD_ShowString(86,150, "RIGHT ");
					break;
				case 34:
					LCD_ShowString(86,150, "LEFT  ");
					break;
				case 56:
					LCD_ShowString(86,150, "8     ");
					break;
				case 224:
					LCD_ShowString(86,150, "VOL-  ");
					break;
				case 168:
					LCD_ShowString(86,150, "DOWN  ");
					break;
				case 144:
					LCD_ShowString(86,150, "VOL+  ");
					break;
				case 104:
					LCD_ShowString(86,150, "1     ");
					break;
				case 152:
					LCD_ShowString(86,150, "2     ");
					break;
				case 176:
					LCD_ShowString(86,150, "3     ");
					break;
				case 48:
					LCD_ShowString(86,150, "4     ");
					break;
				case 24:
					LCD_ShowString(86,150, "5     ");
					break;
				case 122:
					LCD_ShowString(86,150, "6     ");
					break;
				case 16:
					LCD_ShowString(86,150, "7     ");
					break;
				case 90:
					LCD_ShowString(86,150, "9     ");
					break;
				case 66:
					LCD_ShowString(86,150, "0     ");
					break;
				case 82:
					LCD_ShowString(86,150, "DELETE");
					break;	    
			}
		}else delay_ms(2);
		t++;
		if(t==200)
		{
			t=0;
			LED0=!LED0;
		}
	}

}

