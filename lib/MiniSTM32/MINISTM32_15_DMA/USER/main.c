#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "dma.h"

//Mini STM32�����巶������15
//DMA ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com

u8 SendBuff[5200];
const u8 TEXT_TO_SEND[]={"ALIENTEK MiniSTM32 DMA ����ʵ��"}; 
 int main(void)
 {
	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;//����

	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();

	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,5200);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����5200.

 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DMA USART TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");
	//��ʾ��ʾ��Ϣ
	LCD_ShowString(60,130,"Press KEY0 To Start!");

	j=sizeof(TEXT_TO_SEND);	   
	for(i=0;i<5200;i++)//���ASCII�ַ�������
    {
		if(t>=j)//���뻻�з�
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}   	   
    }		 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
	while(1)
	{
		t=KEY_Scan();
		if(t==1)//KEY0����
		{
			LCD_ShowString(60,150,"Start Transimit....");
			LCD_ShowString(60,170,"   %");//��ʾ�ٷֺ�
			printf("\n\nDMA DATA:\n"); 	    
		    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);           //ʹ�ܴ���1��DMA����       
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4) == SET)//�ȴ�ͨ��4�������
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);  //���������ɱ�־
					break; 
		        }
				pro = DMA_GetCurrDataCounter(DMA1_Channel4);    //�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/5200;//�õ��ٷֱ�	  
				pro*=100;      //����100��
				LCD_ShowNum(60,170,pro,3,16);	  
		    }			    
			LCD_ShowNum(60,170,100,3,16);//��ʾ100%	  
			LCD_ShowString(60,150,"Transimit Finished!");//��ʾ�������
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

