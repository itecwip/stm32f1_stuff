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
//Mini STM32�����巶������12
//�������� ʵ��
//����ԭ��@ALIENTEK
//����֧����̳��www.openedv.com
 
 int main(void)
 {
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
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

