// DAC.c
// This software configures DAC output
// Labs 6 and 10 requires 6 bits for the DAC
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/2/23 
// Lab number: 6
// Hardware connections
// PE0-5

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R & 0x10) == 0) {
	}
	
	GPIO_PORTE_DIR_R |= 0x3F;
	GPIO_PORTE_DR8R_R |= 0x3F;
	GPIO_PORTE_DEN_R |= 0x3F;
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Input=n is converted to n*3.3V/63
// Output: none
void DAC_Out(uint8_t data){
  GPIO_PORTE_DATA_R = (GPIO_PORTE_DATA_R & ~0x3F) | (data & 0x3F);
}
