#ifndef __GRID_H
#define __GRID_H

#include <stdint.h>
#include <stdbool.h>
#include "pieces.h"

// the actual visible grid (solidified minos only)
extern uint8_t matrix[22][10];
// the changes in the visible grid
extern piece_t currPiece;
extern piece_t heldPiece;
extern int8_t pX, pY, pRot;

uint8_t testOrientation(piece_t piece, 
												uint8_t rot,
												uint8_t x, uint8_t y);

// (re)initializes the grid
void Grid_Init();
// pulls a new piece from the piece queue
void Grid_NewPiece();
// clears the changes matrix
static void Grid_ClearChanges();
// draws the grid
void Grid_Draw();
// clears lines on the grid, updates changes accordingly
// returns how many lines are cleared
uint8_t Grid_ClearLines();
// rotates the piece (true for cwise, false for ccwise)
void Grid_RotatePiece(bool cwise);
// moves the piece sideways once (true for right, false for left)
void Grid_TranslatePiece(bool right);
// drops the piece down once
void Grid_SoftDrop();
// hard drops the piece
void Grid_HardDrop();
// locks the piece in place
void Grid_LockPiece();
// holds the current piece
void Grid_HoldPiece();

#endif // __GRID_H