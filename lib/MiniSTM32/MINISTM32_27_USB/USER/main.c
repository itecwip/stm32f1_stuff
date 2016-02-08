#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "spi.h"
#include "usart.h"
#include "mmc_sd.h"
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_istr.h"
#include <stdio.h>
//Mini STM32�����巶������27
//USB������ ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com

//bit0:��ʾ����������SD��д������
//bit1:��ʾ��������SD����������
//bit2:SD��д���ݴ����־λ
//bit3:SD�������ݴ����־λ
//bit4:1,��ʾ��������ѯ����(�������ӻ�������)
u8 Usb_Status_Reg=0;

int main(void)
{	
 	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
  
	LCD_Init();
 
   	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"USB TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/6/19");	

	while(SD_Init())
	{
		LCD_ShowString(60,130,"SD Init ERR!");	
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check");	
		delay_ms(500);
	}					  													 
	LCD_ShowString(60,130,"SD Card Ready");//��ʾSD���Ѿ�׼����	 
    Mass_Memory_Size[0]=SD_GetCapacity();//�õ�SD������
    Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
	LCD_ShowString(60,150,"USB Connecting...");//��ʾSD���Ѿ�׼����	 
	//USB����
	USB_Interrupts_Config();    
	Set_USBClock();   
	USB_Init();	  	 								   	 
	while(1)
	{	
		delay_ms(1);
		if(USB_STA!=Usb_Status_Reg)//״̬�ı��� 
		{	 						   
			LCD_ShowString(60,170,"              ");//���  
			if(Usb_Status_Reg&0x01)//����д		  
			{
				LCD_ShowString(60,170,"USB Writing...");//��ʾUSB����д������	 
			}
			if(Usb_Status_Reg&0x02)//���ڶ�
			{
				LCD_ShowString(60,170,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}	 										  
			if(Usb_Status_Reg&0x04)LCD_ShowString(60,190,"USB Write Err ");//��ʾд�����
			else LCD_ShowString(60,190,"              ");//�������    
			if(Usb_Status_Reg&0x08)LCD_ShowString(60,210,"USB Read  Err ");//��ʾ��������
			else LCD_ShowString(60,210,"              ");//�������    
			USB_STA=Usb_Status_Reg;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,150,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else LCD_ShowString(60,150,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//��ʾϵͳ������
			if(Usb_Status_Reg&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
			}
			Usb_Status_Reg=0;
		}
	};	   		  
 
}
