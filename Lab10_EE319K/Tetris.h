#include <stdint.h>
#include "../inc/wave.h"
#include "pieces.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

typedef enum {English, Spanish} Language_t; 
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";

uint8_t currentRot;
piece_t currentPiece; //Colored Square of Current Piece
uint8_t pieceX;
uint8_t pieceY;
int8_t grid[22][10]; //Stationary Grid
int8_t lastGrid[22][10]; //Stores Last state of Active Piece
int8_t newGrid[22][10]; //Stores New state of Active Piece due to Gravity, Drops, Shifts and Rotations

//Sounds Stuff
void Wave_SoundTick(uint8_t channels);
void Wave_SetChannel(soundchannel_t channel, int16_t data);


void resetBoard(); //Clears Grid Array
void spawnPiece(piece_t piece, uint8_t offset); 
void shift(uint8_t rotation, uint8_t deltaX, uint8_t deltaY); //Shifts Active Piece (Check First)
uint8_t canMove(uint8_t rotation, uint8_t deltaX, uint8_t deltaY); //Detects if the Active Piece can make the move specified
uint8_t clearLines(); //Check for Full Lines, Clear them if full (returns num of Lines Cleared)
void GameLoop(); //Main Update Method
void solidify(); //Adds Active Piece to Main Grid