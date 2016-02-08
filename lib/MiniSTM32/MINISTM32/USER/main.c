#include "led.h"
#include "delay.h"
#include "sys.h"
//Mini STM32开发板范例代码1
//跑马灯实验		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//实验现象：
// DS0 ,DS1闪烁，时间间隔为300ms.
//详细的实验现象以及硬件连接请查看《STM32不完全手册》3.2按键输入实验
	
 int main(void)
 {
 	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
		while(1)
	{
 		LED0=0;				 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
 		LED1=1;	 			 //	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay_ms(300);		 
 	 	LED0=1;	             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);	    
  		LED1=0; 			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
		delay_ms(300);	
		}
 }

