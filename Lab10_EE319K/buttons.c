#include "buttons.h"


bool sDropPressed;
bool hDropPressed;
bool rotateCWPressed;
bool rotateCCWPressed;
bool holdPressed;

void Button_Init(void){       
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
	
	sDropPressed = false;
	hDropPressed = false;
	rotateCWPressed = false;
	rotateCCWPressed = false;
	holdPressed = false;

  GPIO_PORTE_DIR_R &= ~0x02;    // (c) make PE0-4 in (built-in button)
  GPIO_PORTE_DEN_R |= 0x02;     //     enable digital I/O on PE0-4
  GPIO_PORTE_PDR_R |= 0x02;     //     enable weak pull-down on PE0-4
  GPIO_PORTE_IS_R &= ~0x02;     // (d) PE0-4 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x02;    //     PE0-4 is not both edges
  GPIO_PORTE_IEV_R |= 0x02;    //     PE0-4 rising edge event
  GPIO_PORTE_ICR_R |= 0x02;      // (e) clear flags
  GPIO_PORTE_IM_R |= 0x02;      // (f) arm interrupt on PE0-4
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF1F)|0x00000000; // (g) priority 0
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
}

void GPIOPortE_Handler(void)
{
	//Grab RIS (Ha RIZZ) Register 
	//Set Boolean Flags
	if(GPIO_PORTE_RIS_R > 0)
	{
		sDropPressed = (GPIO_PORTE_RIS_R&0x01);
		hDropPressed = (GPIO_PORTE_RIS_R&0x02);
		rotateCWPressed = (GPIO_PORTE_RIS_R&0x04);
		rotateCCWPressed = (GPIO_PORTE_RIS_R&0x08);
		holdPressed = (GPIO_PORTE_RIS_R&0x10);
	}
	
	//Acknowledge Neccessary Flags in Interrupt
  GPIO_PORTE_ICR_R = 0x1F;      // acknowledge all flags
}