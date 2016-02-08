#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"

//Mini STM32�����巶������8
//PWM��� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	 
 int main(void)
 {
	u16 led0pwmval=0;
	u8 dir=1;
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //������ʼ��	
	PWM_Init(900,0);	 //����Ƶ��PWMƵ��=72000/900=8Khz
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

