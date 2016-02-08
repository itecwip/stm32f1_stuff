#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"

//Mini STM32开发板范例代码8
//PWM输出 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	 
 int main(void)
 {
	u16 led0pwmval=0;
	u8 dir=1;
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //按键初始化	
	PWM_Init(900,0);	 //不分频。PWM频率=72000/900=8Khz
		while(1)
	{
 		delay_ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>300)dir=0;
		if(led0pwmval==0)dir=1;	
												 
		TIM_SetCompare2(TIM3,led0pwmval);	   
	}	 

 }

