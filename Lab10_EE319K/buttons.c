#include "buttons.h"

void Button_Init(void){       
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
	
	sDropPressed = false;
	hDropPressed = false;
	rotateCWPressed = false;
	rotateCCWPressed = false;
	holdPressed = false;

  GPIO_PORTE_DIR_R &= ~0x1F;    // (c) make PE0-4 in (built-in button)
  GPIO_PORTE_DEN_R |= 0x1F;     //     enable digital I/O on PE0-4
  GPIO_PORTE_PDR_R |= 0x1F;     //     enable weak pull-down on PE0-4
  GPIO_PORTE_IS_R &= ~0x1F;     // (d) PE0-4 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x1F;    //     PE0-4 is not both edges
  GPIO_PORTE_IEV_R &= 0x1F;    //     PE0-4 rising edge event
  GPIO_PORTE_ICR_R = 0x1F;      // (e) clear flags
  GPIO_PORTE_IM_R |= 0x1F;      // (f) arm interrupt on PE0-4
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF1F)|0x000000A0; // (g) priority 5
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
}

void GPIOPortE_Handler(void)
{
	//Grab RIS (Ha RIZZ) Register 
	//Set Boolean Flags
	//Acknowledge Neccessary Flags in Interrupt
  GPIO_PORTE_ICR_R = 0x1F;      // acknowledge all flags
}