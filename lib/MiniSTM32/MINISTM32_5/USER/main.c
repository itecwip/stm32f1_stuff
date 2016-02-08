#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
//ALIENTEK Mini STM32�����巶������5
//�������Ź�ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	

 int main(void)
 {
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();          //������ʼ��	 
	delay_ms(300);   	 //���˿��õ���
	IWDG_Init(IWDG_Prescaler_64,625);
	LED0=0;				 //����LED0
	while(1)
	{
		if(KEY_Scan()==3)IWDG_Feed();//���WK_UP����,��ι��
		delay_ms(10);
	};	 
 }

