// ADC.c
// Runs on TM4C123
// Provide functions that initialize ADC0
// Last Modified: 1/2/2023  
// Student names: Dylan Rogers and Jed Wang
// Last modification date: 3/25/2023
// This file is in the inc folder so it automatically will be applied to labs 8 9 and 10
// Labs 8, 9, and 10 specify PD2
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function using PD2 
// Input: none
// Output: none
void ADC_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x8;
	while((SYSCTL_PRGPIO_R&0x8) == 0){
	}
	GPIO_PORTD_DIR_R &= ~0x4;
	GPIO_PORTD_AFSEL_R |= 0x4;
	GPIO_PORTD_DEN_R &= ~0x4;
	GPIO_PORTD_AMSEL_R |= ~0x4;
	
	SYSCTL_RCGCADC_R |= 0x1;
	while((SYSCTL_PRADC_R & 0x1) == 0){
	}
	ADC0_PC_R = 0x01;
	ADC0_SSPRI_R = 0x0123;
	ADC0_ACTSS_R &= ~0x0008;
	ADC0_SAC_R = 4;
	ADC0_EMUX_R &=  ~0xF000;
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+5;
	ADC0_SSCTL3_R = 0x0006;
	ADC0_IM_R &= ~0x0008;
	ADC0_ACTSS_R |= 0x0008;		
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  
	uint32_t data;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R&0x08)==0){};
	data = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R = 0x0008;
	return data;
}

int8_t slideInput(void)
{
	uint16_t slider = ADC_In();
	if(slider > 3895)
		return 2;
	else if(slider <= 200)
		return -2;
	else if(slider <= 3895 && slider > 2664)
		return 1;
	else if(slider <= 2664 && slider > 1432)
		return 0;
  else
		return -1;
}

