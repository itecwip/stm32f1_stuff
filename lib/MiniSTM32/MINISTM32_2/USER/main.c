#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"

//Mini STM32�����巶������2
//��������ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	 

 int main(void)
 {
	u8 t;	
 	SystemInit();  //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();	//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();	//��ʼ���밴�����ӵ�Ӳ���ӿ�
		while(1)
	{
		t=KEY_Scan();//�õ���ֵ
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:
					LED0=!LED0;
					break;
				case 2:
					LED1=!LED1;
					break;
				case 3:				
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}	 

 }

