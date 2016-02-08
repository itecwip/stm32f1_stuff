#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
//ALIENTEK Mini STM32开发板范例代码5
//独立看门狗实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	

 int main(void)
 {
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //按键初始化	 
	delay_ms(300);   	 //让人看得到灭
	IWDG_Init(IWDG_Prescaler_64,625);
	LED0=0;				 //点亮LED0
	while(1)
	{
		if(KEY_Scan()==3)IWDG_Feed();//如果WK_UP按下,则喂狗
		delay_ms(10);
	};	 
 }

