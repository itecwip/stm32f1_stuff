#include "led.h"
#include "delay.h"
#include "sys.h"
//Mini STM32�����巶������1
//�����ʵ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//ʵ������
// DS0 ,DS1��˸��ʱ����Ϊ300ms.
//��ϸ��ʵ�������Լ�Ӳ��������鿴��STM32����ȫ�ֲᡷ3.2��������ʵ��
	
 int main(void)
 {
 	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
		while(1)
	{
 		LED0=0;				 //  ����ʹ����λ��������Ҳ����ʹ�� GPIO_ResetBits(GPIOA,GPIO_Pin_8);
 		LED1=1;	 			 //	 Ҳ����ʹ��   GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay_ms(300);		 
 	 	LED0=1;	             //	 Ҳ����ʹ��	  GPIO_SetBits(GPIOA,GPIO_Pin_8);	    
  		LED1=0; 			 // Ҳ����ʹ��	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
		delay_ms(300);	
		}
 }

