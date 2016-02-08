#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"

//ALIENTEK Mini STM32开发板范例代码7
//定时器中断 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	

 int main(void)
 {
   	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);   //串口初始化
 	LED_Init();		   //LED端口初始化
	KEY_Init();          //按键端口初始化
	Timerx_Init(5000,7199);//10Khz的计数频率，计数到5000为500ms 
	while(1)
	{
		LED0=!LED0;
		delay_ms(200);		   
	}
 }

