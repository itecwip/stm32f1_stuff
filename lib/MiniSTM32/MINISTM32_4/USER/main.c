#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
//Mini STM32�����巶������4
//�ⲿ�ж�ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	  

//ע��,�˴��뻹���޷�����SWD����!��Ϊʹ�����ж�,û������ͨ�ķ��������Ǽ�Ъ����SWD��! 
 int main(void)
 {
 	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);      //���ڳ�ʼ��
 	LED_Init();			  //LED�˿ڳ�ʼ��
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
	while(1)
	{	    
		printf("OK\n");	
		delay_ms(1000);	  
	}

 }

