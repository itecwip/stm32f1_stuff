#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������13
//ADC ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
 
 int main(void)
 {
	u16 adcx;
	float temp;
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	Adc_Init();
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"ADC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,"ADC_CH0_VOL:0.000V");	      
	while(1)
	{
		adcx=Get_Adc(ADC_Channel_0);
		LCD_ShowNum(156,130,adcx,4,16);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowNum(156,150,adcx,1,16);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowNum(172,150,temp,3,16);
		LED0=!LED0;
		delay_ms(250);
	}

 }

