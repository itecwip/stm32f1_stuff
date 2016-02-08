#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
#include "mmc_sd.h"
#include "mouse.h"
//Mini STM32�����巶������23
//PS2��� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com


//ע��,������벻����JTAG/SWD����.����SWD������������.
 int main(void)
 {  	
 	u8 t;
	u8 errcnt=0;
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
	LCD_Init();
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"PS2 Mouse TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/6/17");			  
RST:t=Init_Mouse();
	if(t==0)LCD_ShowString(60,130,"Mouse Init OK!");
	else
	{
		printf("ERROR_CODE:%d\n",t);
		LCD_ShowString(60,130,"Error CODE:");
		LCD_ShowNum(148,130,t,3,16);//���ģʽ
		LED0=!LED0;
		//delay_ms(500);
		goto RST;
	}  
	POINT_COLOR=BLUE;
	LCD_ShowString(60,150,"Mouse ID:");
 	LCD_ShowNum(132,150,MOUSE_ID,3,16);//���ģʽ


	LCD_ShowString(30,170,"BUF[0]:");
	LCD_ShowString(30,186,"BUF[1]:");
	LCD_ShowString(30,202,"BUF[2]:"); 
	if(MOUSE_ID==3)LCD_ShowString(30,218,"BUF[3]:"); 

	LCD_ShowString(90+30,170,"X  POS:");
	LCD_ShowString(90+30,186,"Y  POS:");
	LCD_ShowString(90+30,202,"Z  POS:"); 
	if(MOUSE_ID==3)LCD_ShowString(90+30,218,"BUTTON:"); 
	t=0;
	while(1)
	{
		if(PS2_Status&0x80)//�õ���һ������
		{		  
			LCD_ShowNum(56+30,170,PS2_DATA_BUF[0],3,16);//���ģʽ
			LCD_ShowNum(56+30,186,PS2_DATA_BUF[1],3,16);//���ģʽ
			LCD_ShowNum(56+30,202,PS2_DATA_BUF[2],3,16);//���ģʽ
			if(MOUSE_ID==3)LCD_ShowNum(56+30,218,PS2_DATA_BUF[3],3,16);//���ģʽ

			Mouse_Data_Pro();//��������
			LCD_ShowNum(146+30,170,MouseX.x_pos,5,16);//���ģʽ
			LCD_ShowNum(146+30,186,MouseX.y_pos,5,16);//���ģʽ
			if(MOUSE_ID==3)LCD_ShowNum(146+30,202,MouseX.z_pos,5,16);//���ģʽ

		    if(MouseX.bt_mask&0x01)LCD_ShowString(146+30,218,"LEFT"); 
			else LCD_ShowString(146+30,218,"    "); 
		    if(MouseX.bt_mask&0x02)LCD_ShowString(146+30,234,"RIGHT"); 
			else LCD_ShowString(146+30,234,"     "); 				    
			if(MouseX.bt_mask&0x04)LCD_ShowString(146+30,250,"MIDDLE"); 
			else LCD_ShowString(146+30,250,"      ");   		 
			PS2_Status=MOUSE;
			PS2_En_Data_Report();//ʹ�����ݱ���
		}else if(PS2_Status&0x40)
		{
			errcnt++;
			PS2_Status=MOUSE;
			LCD_ShowNum(86+30,234,errcnt,3,16);//���ģʽ
		}
		t++;
		delay_ms(1);
		if(t==200)
		{
			t=0;
			LED0=!LED0;
		}
	} 		   

}

