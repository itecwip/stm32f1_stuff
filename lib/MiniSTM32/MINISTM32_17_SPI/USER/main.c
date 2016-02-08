#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"

//Mini STM32�����巶������17
//SPI ʵ��
//����ԭ��@ALIENTEK
//����֧����̳��www.openedv.com
//Ҫд�뵽W25X16���ַ�������

const u8 TEXT_Buffer_SPI[]={"MiniSTM32 SPI TEST"};

#define SIZE sizeof(TEXT_Buffer_SPI)

 int main(void)
 {
   	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];	
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	SPI_Flash_Init();   //SPI FLASH ��ʼ�� 

 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"SPI TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/6/11");	
			 
	while(SPI_Flash_ReadID()!=FLASH_ID)//��ⲻ��W25X16
	{	   
		i=SPI_Flash_ReadID();
		printf("ID:%d",i);
		LCD_ShowString(60,130,"W25X16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"   Please Check!    ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	LCD_ShowString(60,130,"W25X16 Ready!");
	//��ʾ��ʾ��Ϣ
	LCD_ShowString(60,150,"KEY0:Write KEY2:Read");

	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan();
		if(key==1)//KEY0����,д��SPI FLASH
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,"Start Write W25X16....");
			SPI_Flash_Write((u8*)TEXT_Buffer_SPI,1000,SIZE);//��1000�ֽڴ���ʼ,д��SIZE���ȵ�����
			LCD_ShowString(60,170,"W25X16 Write Finished!");//��ʾ�������
		}
		if(key==3)//WK_UP����,��ȡд����ַ����ַ�������ʾ
		{
 			LCD_ShowString(60,170,"Start Read W25X16.... ");
			SPI_Flash_Read(datatemp,1000,SIZE);//��1000��ַ����ʼ,����SIZE���ֽ�
			LCD_ShowString(60,170,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,190,datatemp);//��ʾ�������ַ���
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
 }

