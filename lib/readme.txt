#include "adc.h"

// ADC initialization
// Ch0---->PA0
// Ch1---->PA1
// Ch2---->PA2
// Ch3---->PA3
void  Adc_Init(void)
{
	// GPIO settings
 	RCC->APB2ENR |= 1 << 2;		// enable PORTA
	GPIOA->CRL &= 0XFFFFF000;	// PA0 PA1 PA2 PA3	analog mode
  
	// ADC1 settings
	RCC->APB2ENR |= 1 << 9;    	// enable ADC1
	RCC->APB2RSTR |= 1 << 9;   	// reset ADC1 - bit9
	RCC->APB2RSTR &= ~(1 << 9);	// end of reset ADC1 - bit9

	RCC->CFGR &= ~(3 << 14);	// clear bit15-bit14  ADC prescaler
	RCC->CFGR |= 2 << 14;		// bit15-bit14  ADC PRE = 10 : PCLK2 divided by 6 : 72MHz/6 = 12MHz

	ADC1->CR1 &= 0X00F0FFFF;   // Independent mode,  Analog watchdog disabled on regular channels and on injected channels
	ADC1->CR1 |= 0 << 16;      // Independent mode
	ADC1->CR1 &= ~(1 << 8);    // Scan mode disabled
	ADC1->CR2 &= ~(1 << 1);    // Single conversion mode

	ADC1->CR2 &= ~(7 << 17);   // clear EXTSEL
	ADC1->CR2 |= 7 << 17;	   // set EXTSEL = SWSTART

	ADC1->CR2 |= 1 << 20;      // Conversion on external event enabled
	ADC1->CR2 &= ~(1 << 11);   // clear ALIGN = Right Alignment
	ADC1->CR2 |= 1 << 23;      // TSVREFE: Temperature sensor and VREFINT channel enabled

	ADC1->SQR1 &= ~(0XF << 20);	// Clear Regular channel sequence length
	ADC1->SQR1 |= 0 << 20;		// one conversion

	ADC1->SMPR2 &= ~(7 << 3);	// Clear SMP1
 	ADC1->SMPR2 |= 7 << 3;		// SMP1 : channel 1 = 239.5 cycles

 	ADC1->SMPR1 &= ~(7 << 18);	// Clear SMP16
	ADC1->SMPR1 |= 7 << 18;		// SMP16 : channel 16 = 239.5 cycles (temperature sensor)

	ADC1->CR2 |= 1 << 0;		// A/D convert on
	ADC1->CR2 |= 1 << 3;		// Reset calibration register (RSTCAL = 1)
	while(ADC1->CR2 & 1 << 3);	// wait end of reset (RSTCAL = 0)

	ADC1->CR2 |= 1 << 2;		// Enable A/D calibration (CAL = 1)
	while(ADC1->CR2 & 1 << 2);	// wait end of calibration (CAL = 0)

}				  

// Get ADC value
// ch: channel number [0..16]
uint16_t Get_Adc(uint8_t ch)
{
	ADC1->SQR3 &= 0XFFFFFFE0;		// Clear SQ1 : 1st conversion in regular sequence
	ADC1->SQR3 |= ch;				// Set channel number in SQ1
	ADC1->CR2 |= 1 << 22;			// Start conversion (SWSTART)
	while(!(ADC1->SR & 1 << 1));	// Wait end of conversion (EOC)
	return ADC1->DR;				// Read the ADC value
}


// Return the average of 'times' ADC read
// ch: channel number [0..16]
// times : Number of reads
uint16_t Get_Adc_Average(uint8_t ch, uint8_t times)
{
	uint32_t temp_val = 0;
	for(uint8_t t = 0;t < times;t++) {
		temp_val += Get_Adc(ch);
	}
	return temp_val/times;
} 
