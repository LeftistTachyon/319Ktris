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


int main(void)
{ 
  DisableInterrupts();
  TExaS_Init(SCOPE);       // Bus clock is 80 MHz 
	EnableInterrupts();
	
	// DAC_Init();
	// Wave_Init();
	
	//Timer2A_Start(); // start the sound
	
  Output_Init();
	resetBoard();
	// ST7735_FillScreen(ST7735_BLACK);
	ST7735_FillRect(0, 0, 48, 160, ST7735_WHITE);
	ST7735_FillRect(48, 0, 80, 160, ST7735_BLACK);
	
	// spawnPiece(P_S,0);
	// Timer4A_Init(&GameLoop, 2666667, 6);
	
	// PQ_Init();
	Grid_Init();
	Grid_NewPiece();
		
	while(1) 
	{
		GameLoop();
	}
}

uint32_t frameCount = 0;
bool changeOccured = false;

void GameLoop()
{	
	//Get State of Input
	//Run Logic
	
	//Solidify Check
	//Shifts
	//Rotate
	
	//Gravity
	if(frameCount > 30)
	{
		Grid_DropPiece();
		changeOccured = 1;
		frameCount = 0;
	}
	
	if(frameCount == 10)
	{
		Grid_TranslatePiece(true);
		changeOccured = 1;
	}
	
	if(frameCount == 20)
	{
		Grid_TranslatePiece(false);
		changeOccured = 1;
	}
	if(frameCount == 15)
	{
		Grid_RotatePiece(true);
		changeOccured = 1;
	}
	
	if(changeOccured)
	{
		//Draw to Screen
		Grid_Draw();
		
		changeOccured = false;
	}

	++frameCount;
}

void resetBoard()
{
	for (int i = 0; i < 22; i++)
	{
		for(int k = 0; k < 10; k++)
		{
			grid[i][k] = 0;
			lastGrid[i][k] = 0;
			newGrid[i][k] = 0;
		}
	}
}

void spawnPiece(piece_t piece, uint8_t offset)
{
	for (int i = 0; i < 4 ; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			newGrid[i+offset][k+3] = PieceColormaps[piece][0][i][k];
		}
	}
	currentPiece = piece;
	pieceX = 3;
	pieceY = offset;
	currentRot = 0;
}

void shift(uint8_t rotation, uint8_t deltaX, uint8_t deltaY)
{
	pieceY += deltaY;
	pieceX += deltaX;
	for (int i = 0; i < 4 ; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			newGrid[i+pieceY][k+pieceX] = PieceColormaps[currentPiece][rotation][i][k];
		}
	}
}

//Adds Preivous State of Active Piece to Screen
void solidify()
{
	for (int i = 0; i < 22; i++)
	{
		for(int k = 0; k < 10; k++)
		{
			grid[i][k] = lastGrid[i][k];
		}
	}
}

void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}

