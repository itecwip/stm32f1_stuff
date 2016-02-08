#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"
#include "lcd.h"
#include "wkup.h"
//Mini STM32开发板范例代码12
//待机唤醒 实验
//正点原子@ALIENTEK
//技术支持论坛：www.openedv.com
 
 int main(void)
 {
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	WKUP_Init();
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}

 }

