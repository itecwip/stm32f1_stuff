#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
//Mini STM32�����巶������6
//���ڿ��Ź�ʵ��
//����ԭ��@ALIENTEK
//����֧����̳��www.openedv.com
   

 int main(void)
 {
 	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //������ʼ��	 
	LED0=0;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		LED0=1;			  	   
	}	 
 }

