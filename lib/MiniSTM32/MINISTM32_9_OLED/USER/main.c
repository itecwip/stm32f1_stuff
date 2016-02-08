#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"
#include "oled.h"

//Mini STM32开发板范例代码9
//OLED显示 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	
   

 int main(void)
 {	
 	u8 t=0;	
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
   	OLED_Init();			//初始化OLED     
 	OLED_ShowString(0,0, "0.96' OLED TEST");  
 	OLED_ShowString(0,16,"ATOM@ALIENTEK");  
 	OLED_ShowString(0,32,"2010/06/3");  

 	OLED_ShowString(0,48,"ASCII:");  
 	OLED_ShowString(63,48,"CODE:");  
	OLED_Refresh_Gram();	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
		OLED_Refresh_Gram();
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);//显示ASCII字符的码值 
		delay_ms(300);
	}	  

 }

