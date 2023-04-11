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
#include "Tetris.h"


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
uint8_t failCount = 0;
void GameLoop()
{
	//Get State of Input
	
	
	//Check Overall Game State (Loss Condition)
	
	//Solidify Check (No Moves Made after Given Grace Period)
	if(failCount > 4)
	{
		solidify();
		if(clearLines() > 0)
		{
			redrawBoard();
		}
		spawnPiece(P_S, 0);
		failCount = 0;
	}
	
	//Gravity
	if(frameCount > 15)
	{
		if(canMove(currentRot, 0, 1) == 1)
		{
			shift(currentRot, 0, 1);
		}
		else
		{
			failCount++;
		}
	  frameCount = 0;
	}
	
	//Shifts
	//Rotate
	
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
						ST7735_DrawBitmap(k*8 + 48, (i*8)-8, &SquareBitmaps[0][0], 8, 8);
					if(lastGrid[i][k] - newGrid[i][k] < 0)
						ST7735_DrawBitmap(k*8 + 48, (i*8)-8, &SquareBitmaps[currentPiece+1][0], 8, 8);
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

void redrawBoard()
{
	ST7735_FillScreen(0);
	for (int i = 0; i < 22; i++)
		{
			for(int k = 0; k < 10; k++)
			{
				if (i > 1)
				{
					ST7735_DrawBitmap(k*8 + 48, (i*8)-8, &SquareBitmaps[grid[i][k]][0],8,8);
				}
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
	changeOccured = 1;
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
	
	//Clear Last Grid as Active Piece is no longer the Active Piece
	for (int i = 0; i < 22; i++)
	{
		for(int k = 0; k < 10; k++)
		{
			lastGrid[i][k] = 0;
		}
	}
	changeOccured = 1;
}

//Tests Shift (Returns 0 on fail, 1 on Success)
//Implement Kick Table
uint8_t canMove(uint8_t rotation, uint8_t deltaX, uint8_t deltaY)
{
	uint8_t tempY = pieceY + deltaY;
	uint8_t tempX = pieceX + deltaX;
	
	for (int i = 0; i < 4 ; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if(PieceColormaps[currentPiece][rotation][i][k] != 0)
			{
				if(i+tempY > 21 || i+tempY < 0)
					return 0;
				else if(k+tempX > 9 || k+tempX < 0)
					return 0;
				else if(grid[i+tempY][k+tempX] != 0)
					return 0;
			}
		}
	}
	return 1;
}

//Check for Full Lines, Clear them if full (returns num of Lines Cleared)
uint8_t clearLines()
{
	uint8_t numOfLines = 0;
	for (int i = 21; i >= -1; i--)
	{
		int holeFlag = 0;
		for(int k = 0; k < 10; k++)
		{
			if(i < 21)
			{
				grid[i+1][k] = grid[i+1-numOfLines][k];
			}
			if(i > -1)
			{
				if(grid[i][k] == 0)
					holeFlag = 1;
			}
		}
		if(holeFlag == 0)
			numOfLines++;
		holeFlag = 0;
	}
	return numOfLines;
}

void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}

