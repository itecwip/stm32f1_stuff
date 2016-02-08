#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "mmc_sd.h"
#include "ff.h"
#include "integer.h"
#include "diskio.h"
#include "text.h"
#include "24cxx.h"
#include "fontupd.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "touch.h"
//Mini STM32�����巶������26
//����USB��� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com


//װ�ػ�ͼ�Ľ���
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(216,0,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}
int main(void)
{	
	u8 key;
	u8 i=0;
	u8 tpx=0;	  
	s8 x0;		 //���͵����Զ˵�����ֵ
	s8 y0;
	short xlast; //���һ�ΰ��µ�����ֵ
	short ylast;			  
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	//USB����
	USB_Interrupts_Config();    
	Set_USBClock();   
	USB_Init();	   
 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"USB TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/2");	
	LCD_ShowString(60,130,"Press KEY0 to Adjust");	
	Touch_Init();
	delay_ms(1500);
	Load_Drow_Dialog();	     
	while(1)
	{	
		key=KEY_Scan();
		tpx=AI_Read_TP();//�õ������״̬
		if(tpx)//������������						  
		{											   
			xlast=Pen_Point.X0;
			ylast=Pen_Point.Y0;
			while(1)
			{
				tpx=AI_Read_TP();
				if(tpx==0)break;//�����ɿ���							 
				if(Pen_Point.X0>216&&Pen_Point.Y0<16)Load_Drow_Dialog();//���
				else Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);//��ͼ  
				if((Pen_Point.X0!=xlast||Pen_Point.Y0!=ylast)&&(bDeviceState==CONFIGURED)&&tpx==1)
				{
					x0=(xlast-Pen_Point.X0)*3;//�ϴ�����ֵ��õ�������ֵ֮��,����3��
					y0=(ylast-Pen_Point.Y0)*3;
					xlast=Pen_Point.X0;		  //��¼���ε�����ֵ
					ylast=Pen_Point.Y0;
					Joystick_Send(0,-x0,-y0,0); //�������ݵ�����  
					delay_ms(10);	   
				}else if((bDeviceState==CONFIGURED)&&tpx==2)//����
				{
					tpx=0X01;
					Joystick_Send(tpx,0,0,0);//ģ���������	
				} 
				delay_us(50); 
			} 
			Joystick_Send(0,0,0,0);//��������ɿ�
		}else delay_ms(1);	 
		if(bDeviceState==CONFIGURED)LED1=0;//��USB���óɹ��ˣ�LED1����������
		else LED1=1;
		if(key==1)//KEY0����,��ִ��У׼����
		{
			LCD_Clear(WHITE);//����
		    Touch_Adjust();  //��ĻУ׼ 
			Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i==200)
		{
			i=0;
			LED0=!LED0;
		}
	};	   		  
}   

				 

