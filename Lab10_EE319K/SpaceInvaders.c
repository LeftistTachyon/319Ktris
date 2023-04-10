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


#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "../inc/ADC.h"
#include "Images.h"
#include "Timer1.h"
#include "DAC.h"
#include "../inc/Timer4A.h"
#include "SpaceInvaders.h"


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
	ST7735_FillScreen(0);
	
	spawnPiece(P_S,0);
	Timer4A_Init(&GameLoop, 2666667, 6);
	
	PQ_Init();
		
	while(1) 
	{
	}
}

uint32_t frameCount = 0;
uint8_t changeOccured = 0;
void GameLoop()
{
	
	//Get State of Input
	//Run Logic
	if(frameCount > 30)
	{
		shift(currentRot, 0, 1);
		changeOccured = 1;
		frameCount = 0;
	}
	
	if(frameCount == 10)
	{
		shift(currentRot, 1, 0);
		changeOccured = 1;
	}
	
	if(frameCount == 20)
	{
		shift(currentRot, -1, 0);
		changeOccured = 1;
	}
	if(frameCount == 15)
	{
		currentRot = (currentRot + 1) % 4;
		shift(currentRot, 0, 0);
		changeOccured = 1;
	}
	
	if(changeOccured == 1)
	{
		//Draw to Screen
		for (int i = 0; i < 22; i++)
		{
			for(int k = 0; k < 10; k++)
			{
				if (i > 1)
				{
					if(lastGrid[i][k] - newGrid[i][k] > 0)
						ST7735_DrawBitmap(k*8 + 48, (i*8)-16, &SquareBitmaps[0][0], 8, 8);
					if(lastGrid[i][k] - newGrid[i][k] < 0)
						ST7735_DrawBitmap(k*8 + 48, (i*8)-16, &SquareBitmaps[currentPiece+1][0], 8, 8);
				}
				
				lastGrid[i][k] = newGrid[i][k];
				newGrid[i][k] = 0;
			}
		}
		changeOccured = 0;
	}

	frameCount++;
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

void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}

