// SpaceInvaders.c
// Runs on TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the ECE319K Lab 10

// Last Modified: 1/2/2023 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php

// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// buttons connected to PE0-PE3
// 32*R resistor DAC bit 0 on PB0 (least significant bit)
// 16*R resistor DAC bit 1 on PB1
// 8*R resistor DAC bit 2 on PB2 
// 4*R resistor DAC bit 3 on PB3
// 2*R resistor DAC bit 4 on PB4
// 1*R resistor DAC bit 5 on PB5 (most significant bit)
// LED on PD1
// LED on PD0

#include <stdbool.h>

#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "../inc/ADC.h"
#include "Images.h"
#include "Timer1.h"
#include "DAC.h"
#include "../inc/Timer4A.h"
#include "Tetris.h"
#include "grid.h"
#include "garbage.h"
#include "buttons.h"

int main(void)
{ 
  DisableInterrupts();
  TExaS_Init(SCOPE);       // Bus clock is 80 MHz 
	EnableInterrupts();
	
	// DAC_Init();
	ADC_Init();
	Button_Init();
	// Wave_Init();
	
	//Timer2A_Start(); // start the sound
	
  Output_Init();
	// ST7735_FillScreen(ST7735_BLACK);
	ST7735_FillRect(0, 0, 48, 160, ST7735_WHITE);
	ST7735_FillRect(48, 0, 80, 160, ST7735_BLACK);
	
	Timer4A_Init(&GameLoop, 2666667, 6);
	
	// PQ_Init();
	Grid_Init();
	Grid_NewPiece();
	
	Grid_RotatePiece(true);
		
	while(1)
	{
	}
}

#define GRAVITY_RESET 30
uint8_t gravityCount = GRAVITY_RESET;
#define LOCK_RESET 30
uint8_t lockCount = LOCK_RESET;
#define SOFTDROP_RESET 6
uint8_t softDropCount = SOFTDROP_RESET;

static bool redraw = false;
static uint32_t score;

static void postLockPiece() {
	static uint8_t combo = 0;
	uint8_t linesCleared = Grid_ClearLines(), linesToSend;
	
	if(linesCleared > 0) {
		switch(linesCleared) {
			case 4:
				linesToSend = 4;
				score += 400;
				break;
			case 3:
				linesToSend = 2;
				score += 1000;
				break;
			case 2:
				linesToSend = 1;
				score += 3000;
				break;
			case 1:
				linesToSend = 0;
				score += 12000;
				break;
		}
		linesToSend += combo++;
		
		linesToSend = GQ_CounterGarbage(linesToSend);
		
		// TODO: send garbage
	} else {
		combo = 0;
		// TODO: take damage
	}
	
	gravityCount = GRAVITY_RESET;
	lockCount = LOCK_RESET;
	softDropCount = SOFTDROP_RESET;
	
	Grid_Draw();
	Grid_NewPiece();
	
	redraw = true;
}

bool RIGHT = false;
bool LEFT = false;
uint32_t dasCount = 0;

bool LAST_ROT_R = false;
bool LAST_ROT_L =	false;
bool LAST_HOLD = false;
bool LAST_HARDDROP = false;
bool LAST_SOFTDROP = false;

bool DO_ROT_R = false;
bool DO_ROT_L =	false;
bool DO_HOLD = false;
bool DO_HARDDROP = false;
bool DO_SOFTDROP = false;
void GameLoop()
{
	
	// Get State of Input
	setInputs();
	// Act on input
	// DO_MOVE_R
	if(sliderInput > 0)
	{
		if(RIGHT)
		{
			if(dasCount >= 15)
			{
				Grid_TranslatePiece(true);
				redraw = true;
				dasCount = 0;
			}
			else
				dasCount++;
		}
		else
		{
			dasCount = 1;
			RIGHT = true;
			Grid_TranslatePiece(true);
			redraw = true;
		}
	}
	// DO_MOVE_L
	else if(sliderInput < 0)
	{
		if(LEFT)
		{
			if(dasCount >= 15)
			{
				Grid_TranslatePiece(false);
				redraw = true;
				dasCount = 0;
			}
			else
				dasCount++;
		}
		else
		{
			dasCount = 1;
			LEFT = true;
			Grid_TranslatePiece(false);
			redraw = true;
		}
	}
	else
	{
		dasCount = 0;
		RIGHT = false;
	  LEFT = false;		
	}
	
	if(DO_ROT_R) {
		Grid_RotatePiece(true);
		redraw = true;
	} else if(DO_ROT_L) {
		Grid_RotatePiece(false);
		redraw = true;
	}
	if(DO_HOLD) {
		Grid_HoldPiece();
		redraw = true;
		gravityCount = GRAVITY_RESET;
		lockCount = LOCK_RESET;
	}
	
	// if the user wants to soft drop... 
	if(DO_SOFTDROP) {
		// locking, not dropping
		if(lockCount != LOCK_RESET) {
			lockCount = (lockCount - 1) & 0x08; // hurry up locking
		} else
		// if it's time to soft drop, do it
		if(--softDropCount == 0) {
			Grid_SoftDrop();
			softDropCount = SOFTDROP_RESET;
			redraw = true;
			
			++score;
			
			// post-drop check: if at bottom, start locking
			if(!testOrientation(currPiece, pRot, pX, pY + 1)) {
				--lockCount;
			}
		}
	} else {
		softDropCount = SOFTDROP_RESET; // reset soft drop if not dropping
		
		if(lockCount == LOCK_RESET) { // not locking, dropping
			if(--gravityCount == 0) {
				Grid_SoftDrop();
				gravityCount = GRAVITY_RESET;
				redraw = true;
				
				// post-drop check: if at bottom, start locking
				if(!testOrientation(currPiece, pRot, pX, pY + 1)) {
					--lockCount;
				}
			}
		} else { // not dropping, locking
			--lockCount;
		}
	}
	if(lockCount == 0) {
		Grid_LockPiece();
		lockCount = LOCK_RESET;
		
		postLockPiece();
	} else if(DO_HARDDROP) {
		Grid_HardDrop();
		Grid_Draw();
		
		postLockPiece();
	}
	
	// Draw
	if(redraw)
	{
		//Draw to Screen
		Grid_Draw();
		
		redraw = false;
	}
	
	DisableInterrupts();
	clearInputs();
	EnableInterrupts();
	
}

void setInputs()
{
	sliderInput = slideInput();
	
	if(hDropPressed && !LAST_HARDDROP)
		DO_HARDDROP = true;
	else
		LAST_HARDDROP = false;
	
	if(sDropPressed && !LAST_SOFTDROP)
		DO_SOFTDROP = true;
	else
		LAST_SOFTDROP = false;
	
	if(rotateCWPressed && !LAST_ROT_R)
		DO_ROT_R = true;
	else
		LAST_ROT_R = false;
	
	if(rotateCCWPressed && !LAST_ROT_L)
		DO_ROT_L = true;
	else
		LAST_ROT_L = false;
	
	if(holdPressed && !LAST_HOLD)
		DO_HOLD = true;
	else
		LAST_HOLD = false;
}

void clearInputs()
{
	if(DO_HARDDROP)
	{
		hDropPressed = false;
		LAST_HARDDROP = true;
		DO_HARDDROP = false;
	}
	
	if(DO_SOFTDROP)
	{
		sDropPressed = false;
		LAST_SOFTDROP = true;
		DO_SOFTDROP = false;
	}
	
	if(DO_ROT_R)
	{
		rotateCWPressed = false;
		LAST_ROT_R = true;
		DO_ROT_R = false;
	}
	
	if(DO_ROT_L)
	{
		rotateCCWPressed = false;
		LAST_ROT_L = true;
		DO_ROT_L = false;
	}
	
	if(DO_HOLD)
	{ 
		holdPressed = false;
		LAST_HOLD = true;
		DO_HOLD = false;
	}
}

void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}

