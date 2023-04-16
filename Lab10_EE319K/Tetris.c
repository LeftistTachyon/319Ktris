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
#include "screensel.h"
#include "songs.h"

void ST7735_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	ST7735_DrawFastHLine(x, y, w, color);
	ST7735_DrawFastVLine(x + w - 1, y, h, color);
	ST7735_DrawFastHLine(x, y + h - 1, w, color);
	ST7735_DrawFastVLine(x, y, h, color);
}

int main(void)
{ 
	gameState = Menu;
	langState = English;
	
  DisableInterrupts();
  TExaS_Init(SCOPE);       // Bus clock is 80 MHz 
	// DAC_Init();
	ADC_Init();
	Button_Init();
	Wave_Init();
	EnableInterrupts();
	
	Wave_Start(); // start the sound
	
	Wave_LoopSong(&sauls_nokia);
		
	switchMenu();
	Timer4A_Init(&GameLoop, 2666667, 6);
			
	while(1)
	{
	}
}

#define HOLD_X 7
#define HOLD_Y 9
static void redrawHold() {
	if(heldPiece == P_NONE) {
		ST7735_FillRect(HOLD_X, HOLD_Y + 16, 32, 16, ST7735_WHITE);
		return;
	}
	for(uint8_t y = 1, x, temp; y < 3; ++y) {
		for(x = 0; x < 4; ++x) {
			temp = PieceColormaps[heldPiece][0][y][x];
			ST7735_FillRect(HOLD_X + x * 8, HOLD_Y - 8 + y * 8, 8, 8, temp ? SquareBitmaps[temp][0] : ST7735_WHITE);
		}
	}
}

#define PREVIEW_X 7
#define PREVIEW1_Y 38
#define PREVIEW2_Y 63
#define PREVIEW3_Y 84
static void redrawNextQueue() {
	// piece one
	piece_t piece = PQ_Preview(0);
	if(piece == P_NONE) {
		ST7735_FillRect(PREVIEW_X, PREVIEW1_Y + 16, 32, 16, ST7735_WHITE);
	} else for(uint8_t y = 1, x, temp; y < 3; ++y) {
		for(x = 0; x < 4; ++x) {
			temp = PieceColormaps[piece][0][y][x];
			ST7735_FillRect(PREVIEW_X + x * 8, PREVIEW1_Y - 8 + y * 8, 8, 8, temp ? SquareBitmaps[temp][0] : ST7735_WHITE);
		}
	}
	
	// piece two
	piece = PQ_Preview(1);
	if(piece == P_NONE) {
		ST7735_FillRect(PREVIEW_X, PREVIEW2_Y + 12, 24, 12, ST7735_WHITE);
	} else for(uint8_t y = 1, x, temp; y < 3; ++y) {
		for(x = 0; x < 4; ++x) {
			temp = PieceColormaps[piece][0][y][x];
			ST7735_FillRect(PREVIEW_X + x * 6, PREVIEW2_Y - 6 + y * 6, 6, 6, temp ? SquareBitmaps[temp][0] : ST7735_WHITE);
		}
	}
	
	// piece three
	piece = PQ_Preview(2);
	if(piece == P_NONE) {
		ST7735_FillRect(PREVIEW_X, PREVIEW3_Y + 12, 24, 12, ST7735_WHITE);
	} else for(uint8_t y = 1, x, temp; y < 3; ++y) {
		for(x = 0; x < 4; ++x) {
			temp = PieceColormaps[piece][0][y][x];
			ST7735_FillRect(PREVIEW_X + x * 6, PREVIEW3_Y - 6 + y * 6, 6, 6, temp ? SquareBitmaps[temp][0] : ST7735_WHITE);
		}
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
static bool allowHold = true;

bool RIGHT = false;
bool LEFT = false;
uint32_t dasCount = 0;

static void postLockPiece() {
	static uint8_t combo = 0;
	uint8_t linesCleared = Grid_ClearLines(), linesToSend;
	
	if(linesCleared > 0) {
		switch(linesCleared) {
			case 4:
				linesToSend = 4;
				score += 12000;
				break;
			case 3:
				linesToSend = 2;
				score += 3000;
				break;
			case 2:
				linesToSend = 1;
				score += 1000;
				break;
			case 1:
				linesToSend = 0;
				score += 400;
				break;
		}
		score += combo * 300;
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
	allowHold = true;
	
	ST7735_SetCursor(0,13);
	ST7735_OutUDec(score);
	
	dasCount = 0;
	RIGHT = false;
	LEFT = false;		
	
	Grid_Draw();
	
	if(Grid_NewPiece()) //Check for Death
	{
		switchEnd();
		gameState = End;
	}
	else
	{
		redrawNextQueue();	
		redraw = true;
	}
}

void switchMenu()
{
	ST7735_InitR(SCREEN_TYPE2);
	ST7735_FillScreen(ST7735_WHITE);
	ST7735_DrawBitmap(0,30, logo, 125, 30);
	
	ST7735_FillRect(20,40,88,30,0x0000);
	ST7735_FillRect(20,80,88,30,0x0000);
	ST7735_FillRect(20,120,88,30,0x0000);
	
	ST7735_SetCursor(10,5);
	ST7735_SetTextColor(0xFFFF);
	ST7735_OutString("1P");
	
	ST7735_SetCursor(10,9);
	ST7735_OutString("2P");
	
	ST7735_SetCursor(7,13);
	ST7735_OutString(LangSelect[langState]);\
}

void switchGame()
{
	
	score = 0;
	
	ST7735_InitR(SCREEN_TYPE);
	ST7735_FillRect(0, 0, 48, 160, ST7735_WHITE);
	ST7735_FillRect(48, 0, 80, 160, ST7735_BLACK);
  ST7735_FillRect(0,115,48,65, ST7735_BLACK);
	
	ST7735_FillRect(46, 0, 2, 63, 0b1010110101010101);
	ST7735_FillRect(46, 63, 2, 97, 0b1111100000000000);
	ST7735_DrawRect(2, 4, 42, 26, ST7735_BLACK);
	ST7735_DrawRect(2, 33, 42, 26, ST7735_BLACK);
	ST7735_DrawRect(2, 58, 34, 22, ST7735_BLACK);
	ST7735_DrawRect(2, 79, 34, 22, ST7735_BLACK);
		
	ST7735_SetCursor(0,12);
	ST7735_OutString(LangScore[langState]);
	
	ST7735_SetCursor(0,13);
	ST7735_OutUDec(score);

	
	Grid_Init();
	Grid_NewPiece();
	redrawNextQueue();
}

void switchEnd()
{
	ST7735_InitR(SCREEN_TYPE2);
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_DrawBitmap(0,30, logo, 125, 30);
	
	ST7735_SetCursor(3,4);
	ST7735_OutString(LangGOver[langState]);
	ST7735_SetCursor(5,6);
	ST7735_OutString(LangScore[langState]);
	ST7735_SetCursor(5,7);
	ST7735_OutUDec(score);
}

int8_t buttonSelect = -1;
bool LAST_ROT_R = false;
bool LAST_ROT_L =	false;
bool LAST_HOLD = false;
bool LAST_HARDDROP = false;
// bool LAST_SOFTDROP = false;
int8_t lastSliderInput = -3;

bool DO_ROT_R = false;
bool DO_ROT_L =	false;
bool DO_HOLD = false;
bool DO_HARDDROP = false;
bool DO_SOFTDROP = false;
void GameLoop()
{
	// Get State of Input
	setInputs();
	
	if(gameState == Menu)
	{
		//Select Button
		if(lastSliderInput != sliderInput || buttonSelect == -1)
		{
			ST7735_FillRect(113,32,10,130,0xFFFF);
			if(sliderInput > 0)
			{
				ST7735_FillRect(113,130,10,10,ST7735_BLUE);
				buttonSelect = 2;
			}
			if(sliderInput == 0)
			{
				ST7735_FillRect(113,90,10,10,ST7735_BLUE);
				buttonSelect = 1;
			}
			if(sliderInput < 0)
			{
				ST7735_FillRect(113,50,10,10,ST7735_BLUE);
				buttonSelect = 0;
			}
		}
		
		if(DO_HARDDROP) //Select
		{
			if(buttonSelect == 0)
			{
				switchGame();
				DO_HARDDROP = false;
				gameState = P1;
			}	
			if(buttonSelect == 2)
			{
				DO_HARDDROP = false;
				langState = (langState + 1) % 2;
				switchMenu();
			}
		}
	}
	
	if(gameState == End)
	{
		if(DO_HARDDROP)
		{
			gameState = Menu;
			DO_HARDDROP = false;
			switchMenu();
		}
	}
	
	if(gameState == P1)
	{
		// Act on input
		// DO_MOVE_R
		if(sliderInput != 0 && dasCount-- == 0) {
			Grid_TranslatePiece(sliderInput > 0);
			redraw = true;
			
			if(lastSliderInput == 0) {
				dasCount = 15;
			} else if(sliderInput == 1 || sliderInput == -1) {
				dasCount = 6;
			} else {
				dasCount = 3;
			}
		}
		
		if(DO_ROT_R) {
			Grid_RotatePiece(true);
			redraw = true;
		} else if(DO_ROT_L) {
			Grid_RotatePiece(false);
			redraw = true;
		}
		if(DO_HOLD && allowHold) {
			Grid_HoldPiece();
			redraw = true;
			gravityCount = GRAVITY_RESET;
			lockCount = LOCK_RESET;
			allowHold = false;
			
			dasCount = 0;
			RIGHT = false;
			LEFT = false;		
			
			redrawHold();
		}
		
		// if the user wants to soft drop... 
		if(DO_SOFTDROP) {
			// locking, not dropping
			if(lockCount == LOCK_RESET || 
					testOrientation(currPiece, pRot, pX, pY + 1)) {
				lockCount = LOCK_RESET;
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
				lockCount = (lockCount - 1) & 0x08; // hurry up locking
			}
		} else {
			softDropCount = SOFTDROP_RESET; // reset soft drop if not dropping
			
			if(lockCount == LOCK_RESET || 
					testOrientation(currPiece, pRot, pX, pY + 1)) { // not locking, dropping
				lockCount = LOCK_RESET; // ain't locking
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
				--lockCount; // actually locking
			}
		}
		if(lockCount == 0) {
			Grid_LockPiece();
			lockCount = LOCK_RESET;
			
			postLockPiece();
		} else if(DO_HARDDROP) {
			score += 5 * Grid_HardDrop();
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
	}
	
	DisableInterrupts();
	clearInputs();
	EnableInterrupts();
}

void setInputs()
{
	lastSliderInput = sliderInput;
	sliderInput = slideInput();
	
	DO_HARDDROP = hDropPressed && !LAST_HARDDROP;
	LAST_HARDDROP = hDropPressed;
	
	DO_SOFTDROP = sDropPressed;
	
	DO_ROT_R = rotateCWPressed && !LAST_ROT_R;
	LAST_ROT_R = rotateCWPressed;
	
	DO_ROT_L = rotateCCWPressed && !LAST_ROT_L;
	LAST_ROT_L = rotateCCWPressed;
	
	DO_HOLD = holdPressed && !LAST_HOLD;
	LAST_HOLD = holdPressed;
}

void clearInputs()
{
	hDropPressed = false;
	// sDropPressed = false;
	rotateCWPressed = false;
	rotateCCWPressed = false;
	holdPressed = false;
}

void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}

