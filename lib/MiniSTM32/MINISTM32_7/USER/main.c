#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"

//ALIENTEK Mini STM32�����巶������7
//��ʱ���ж� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	

 int main(void)
 {
   	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);   //���ڳ�ʼ��
 	LED_Init();		   //LED�˿ڳ�ʼ��
	KEY_Init();          //�����˿ڳ�ʼ��
	Timerx_Init(5000,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	while(1)
	{
		LED0=!LED0;
		delay_ms(200);		   
	}
 }

