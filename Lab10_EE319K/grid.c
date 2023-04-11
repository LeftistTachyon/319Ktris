#include "grid.h"
#include "../inc/ST7735.h"

// the actual visible grid (solidified minos only)
uint8_t matrix[22][10];
// the changes in the visible grid
static int8_t changes[22][10];
piece_t currPiece = P_NONE;
piece_t heldPiece = P_NONE;
int8_t pX, pY, pRot;

uint8_t testOrientation(piece_t piece, 
												uint8_t rot,
												uint8_t x, uint8_t y) 
{
	for(uint8_t row = 0, col, absX, absY; row < 4; ++row) {
		for(col = 0; col < 4; ++col) {
			if(PieceColormaps[piece][rot][row][col]) {
				if((absX = x + col) < 0 || 
						absX >= 10 ||
						(absY = y + row) >= 22 || 
						// absY < 0 ||
						matrix[absY][absX])
					return 0;
			}
		}
	}
	
	return 1;
}

// add active piece to changes matrix
static void AddActivePiece() {
	for(uint8_t y = 0, x; y < 4; ++y) {
		if(pY + y < 0) continue;
		if(pY + y >= 22) return;
		
		for(x = 0; x < 4; ++x) {
			if(pX + x >= 0 && pX + x < 22) {
				changes[pY + y][pX + x] += PieceColormaps[currPiece][pRot][y][x];
			}
		}
	}
}
// forcefully add active piece to changes matrix
static void AddActivePieceForce() {
for(uint8_t y = 0, x; y < 4; ++y) {
		if(pY + y < 0) continue;
		if(pY + y >= 22) return;
		
		for(x = 0; x < 4; ++x) {
			if(pX + x >= 0 && pX + x < 22) {
				changes[pY + y][pX + x] = PieceColormaps[currPiece][pRot][y][x];
			}
		}
	}
}
// subtract active piece from changes matrix
static void SubActivePiece() {
	for(uint8_t y = 0, x; y < 4; ++y) {
		if(pY + y < 0) continue;
		if(pY + y >= 22) return;
		
		for(x = 0; x < 4; ++x) {
			if(pX + x >= 0 && pX + x < 22) {
				changes[pY + y][pX + x] -= PieceColormaps[currPiece][pRot][y][x];
			}
		}
	}
}

// (re)initializes the matrix
void Grid_Init() {
	// initialize piece queue
	PQ_Init();
	
	// initialize the pieces
	heldPiece = P_NONE;
	// Grid_NewPiece(); // only if immediate start
	currPiece = P_NONE;
	
	// clear matrices
	for(uint8_t y = 0, x; y < 22; ++y) {
		for(x = 0; x < 10; ++x) {
			matrix[y][x] = 0;
			changes[y][x] = 0;
		}
	}
}

// clears the changes matrix
static void Grid_ClearChanges() {
	for(uint8_t y = 0, x; y < 22; ++y) {
		for(x = 0; x < 10; ++x) {
			changes[y][x] = 0;
		}
	}
}

// pulls a new piece from the piece queue
void Grid_NewPiece() {
	currPiece = PQ_PollPiece();
	// pX = 3;
	pX = 0;
	pY = 1;
	pRot = 0; // TODO: IRS
	
	AddActivePieceForce();
}

#define GRID_X 48
#define GRID_Y -16
// draws the matrix
void Grid_Draw() {
	for(uint8_t y = 2, x; y < 22; ++y) {
		for(x = 0; x < 10; ++x) {
			if(changes[y][x] == 0) continue;
			if(changes[y][x] < 0) {
				// less than zero: blank
				ST7735_DrawBitmap(x*8 + GRID_X, y*8 + GRID_Y + 8, &SquareBitmaps[0][0], 8, 8);
			} else {
				// more than zero: the given color
				ST7735_DrawBitmap(x*8 + GRID_X, y*8 + GRID_Y + 8, &SquareBitmaps[changes[y][x]][0], 8, 8);
			}
		}
	}
	
	Grid_ClearChanges();
}

// clears lines on the matrix, updates changes accordingly
// returns how many lines are cleared
uint8_t Grid_ClearLines() {
	uint8_t cleared = 0, oldY = 21, newY = 21, x;
	
	for(bool all, none; oldY >= 0; --oldY) {
		for(x = 0, all = 1, none = 0; x < 10; ++x) {
			matrix[newY][x] = matrix[oldY][x];
			changes[newY][x] = matrix[oldY][x] == 0 ? -1 : matrix[oldY][x];
			all &= matrix[oldY][x] > 0;
			none |= matrix[oldY][x] > 0;
		}
		
		if(!none) break;
		if(!all) --newY;
		else ++cleared;
	}
	
	for(; newY >= oldY; --newY) {
		for(x = 0; x < 10; ++x) {
			matrix[newY][x] = 0;
			changes[newY][x] = -1;
		}
	}
	
	return cleared;
}

// rotates the piece (true for cwise, false for ccwise)
void Grid_RotatePiece(bool cwise) {
	SubActivePiece();
	
	// rotate
	uint8_t newRot = (pRot + (cwise ? 1 : -1)) & 0b11U;
	
	// check for collisions
	if(testOrientation(currPiece, newRot, pX, pY)) {
		pRot = newRot;
		goto exit;
	}
	
	// special case: LJT no kicks when horizontal
	if(currPiece <= P_T && (pRot ^ 0b01U)) goto exit;
	
	// try one to the right
	if(testOrientation(currPiece, newRot, pX+1, pY)) {
		pRot = newRot;
		++pX;
		goto exit;
	}
	
	// try one to the left
	if(testOrientation(currPiece, newRot, pX-1, pY)) {
		pRot = newRot;
		--pX;
		goto exit;
	}	
	
	exit: AddActivePiece();
}

// moves the piece sideways once (true for right, false for left)
void Grid_TranslatePiece(bool right) {
	if(right) {
		if(testOrientation(currPiece, pRot, pX + 1, pY)) {
			SubActivePiece();
			++pX;
			AddActivePiece();
		}
	} else {
		if(testOrientation(currPiece, pRot, pX - 1, pY)) {
			SubActivePiece();
			--pX;
			AddActivePiece();		
		}
	}
}

// drops the piece down once
void Grid_SoftDrop() {
	if(testOrientation(currPiece, pRot, pX, pY + 1)) {
		SubActivePiece();
		++pY;
		AddActivePiece();
	}
}

// hard drops the piece
void Grid_HardDrop() {
	SubActivePiece();
	while(testOrientation(currPiece, pRot, pX, pY + 1)) {
		++pY;
	}
	AddActivePiece();
	
	Grid_LockPiece();
}

// locks the piece in place
void Grid_LockPiece() {
	for(uint8_t y = 0, x; y < 4; ++y) {
		if(pY + y < 0) continue;
		if(pY + y >= 22) break;
		
		for(x = 0; x < 4; ++x) {
			if(pX + x >= 0 && pX + x < 22) {
				matrix[pY + y][pX + x] = PieceColormaps[currPiece][pRot][y][x];
			}
		}
	}
	
	currPiece = P_NONE;
}
// holds the current piece
void Grid_HoldPiece() {
	SubActivePiece();
	if(heldPiece == P_NONE) {
		heldPiece = currPiece;
		Grid_NewPiece();
	} else {
		piece_t temp = heldPiece;
		heldPiece = currPiece;
		currPiece = temp;
	}
	
	AddActivePieceForce(); // not += for this case, but =
}
