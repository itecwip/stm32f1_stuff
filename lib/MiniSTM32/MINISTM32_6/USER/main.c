#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
//Mini STM32开发板范例代码6
//窗口看门狗实验
//正点原子@ALIENTEK
//技术支持论坛：www.openedv.com
   

 int main(void)
 {
 	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //按键初始化	 
	LED0=0;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//计数器值为7f,窗口寄存器为5f,分频数为8	   
 	while(1)
	{
		LED0=1;			  	   
	}	 
 }

