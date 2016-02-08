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
//Mini STM32开发板范例代码27
//USB读卡器 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com

//bit0:表示电脑正在向SD卡写入数据
//bit1:表示电脑正从SD卡读出数据
//bit2:SD卡写数据错误标志位
//bit3:SD卡读数据错误标志位
//bit4:1,表示电脑有轮询操作(表明连接还保持着)
u8 Usb_Status_Reg=0;

int main(void)
{	
 	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
  
	LCD_Init();
 
   	POINT_COLOR=RED;//设置字体为蓝色	   
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
	LCD_ShowString(60,130,"SD Card Ready");//提示SD卡已经准备了	 
    Mass_Memory_Size[0]=SD_GetCapacity();//得到SD卡容量
    Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
	LCD_ShowString(60,150,"USB Connecting...");//提示SD卡已经准备了	 
	//USB配置
	USB_Interrupts_Config();    
	Set_USBClock();   
	USB_Init();	  	 								   	 
	while(1)
	{	
		delay_ms(1);
		if(USB_STA!=Usb_Status_Reg)//状态改变了 
		{	 						   
			LCD_ShowString(60,170,"              ");//清除  
			if(Usb_Status_Reg&0x01)//正在写		  
			{
				LCD_ShowString(60,170,"USB Writing...");//提示USB正在写入数据	 
			}
			if(Usb_Status_Reg&0x02)//正在读
			{
				LCD_ShowString(60,170,"USB Reading...");//提示USB正在读出数据  		 
			}	 										  
			if(Usb_Status_Reg&0x04)LCD_ShowString(60,190,"USB Write Err ");//提示写入错误
			else LCD_ShowString(60,190,"              ");//清除错误    
			if(Usb_Status_Reg&0x08)LCD_ShowString(60,210,"USB Read  Err ");//提示读出错误
			else LCD_ShowString(60,210,"              ");//清除错误    
			USB_STA=Usb_Status_Reg;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,150,"USB Connected    ");//提示USB连接已经建立
			else LCD_ShowString(60,150,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//提示系统在运行
			if(Usb_Status_Reg&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			Usb_Status_Reg=0;
		}
	};	   		  
 
}
