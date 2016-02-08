#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"
#include "lcd.h"
#include "rtc.h"

//ALIENTEK Mini STM32�����巶������11
//RTCʵʱʱ�� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	  
 	
const u8 *COMPILED_DATE=__DATE__;//��ñ�������
const u8 *COMPILED_TIME=__TIME__;//��ñ���ʱ��

const u8* Week[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

 int main(void)
 {
	u8 t=0;	
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	RTC_Init();
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"RTC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");	
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,"    -  -  ");	   
	LCD_ShowString(60,162,"  :  :  ");		    
	while(1)
	{								    
		if(t!=timer.sec)
		{
			t=timer.sec;
			LCD_ShowNum(60,130,timer.w_year,4,16);									  
			LCD_ShowNum(100,130,timer.w_month,2,16);									  
			LCD_ShowNum(124,130,timer.w_date,2,16);	 
			switch(timer.week)
			{
				case 0:
					LCD_ShowString(60,148,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,162,timer.hour,2,16);									  
			LCD_ShowNum(84,162,timer.min,2,16);									  
			LCD_ShowNum(108,162,timer.sec,2,16);
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  

 }

