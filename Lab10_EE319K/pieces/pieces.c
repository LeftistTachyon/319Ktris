#include "pieces.h"

#define PIECES_VIA_DEFINE
#ifdef PIECES_VIA_DEFINE

// I piece
#define I0 { \
	{BLANK, BLANK, BLANK, BLANK}, \
	{CYAN,  CYAN,  CYAN,  CYAN},  \
	{BLANK, BLANK, BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}
#define I1 { \
	{BLANK, BLANK, CYAN, BLANK}, \
	{BLANK, BLANK, CYAN, BLANK}, \
	{BLANK, BLANK, CYAN, BLANK}, \
	{BLANK, BLANK, CYAN, BLANK}  \
}

// T piece
#define T0 { \
	{BLANK,  BLANK,  BLANK,  BLANK}, \
	{PURPLE, PURPLE, PURPLE, BLANK}, \
	{BLANK,  PURPLE, BLANK,  BLANK}, \
	{BLANK,  BLANK,  BLANK,  BLANK}  \
}
#define T1 { \
	{BLANK,  PURPLE, BLANK, BLANK}, \
	{PURPLE, PURPLE, BLANK, BLANK}, \
	{BLANK,  PURPLE, BLANK, BLANK}, \
	{BLANK,  BLANK,  BLANK, BLANK}  \
}
#define T2 { \
	{BLANK,  BLANK,  BLANK,  BLANK}, \
	{BLANK,  PURPLE, BLANK,  BLANK}, \
	{PURPLE, PURPLE, PURPLE, BLANK}, \
	{BLANK,  BLANK,  BLANK,  BLANK}  \
}
#define T3 { \
	{BLANK, PURPLE, BLANK,  BLANK}, \
	{BLANK, PURPLE, PURPLE, BLANK}, \
	{BLANK, PURPLE, BLANK,  BLANK}, \
	{BLANK, BLANK,  BLANK,  BLANK}  \
}

// L piece
#define L0 { \
	{BLANK,  BLANK,  BLANK,  BLANK}, \
	{ORANGE, ORANGE, ORANGE, BLANK}, \
	{ORANGE, BLANK,  BLANK,  BLANK}, \
	{BLANK,  BLANK,  BLANK,  BLANK}  \
}
#define L1 { \
	{ORANGE, ORANGE, BLANK, BLANK}, \
	{BLANK,  ORANGE, BLANK, BLANK}, \
	{BLANK,  ORANGE, BLANK, BLANK}, \
	{BLANK,  BLANK,  BLANK, BLANK}  \
}
#define L2 { \
	{BLANK,  BLANK,  BLANK,  BLANK}, \
	{BLANK,  BLANK,  ORANGE, BLANK}, \
	{ORANGE, ORANGE, ORANGE, BLANK}, \
	{BLANK,  BLANK,  BLANK,  BLANK}  \
}
#define L3 { \
	{BLANK, ORANGE, BLANK,  BLANK}, \
	{BLANK, ORANGE, BLANK,  BLANK}, \
	{BLANK, ORANGE, ORANGE, BLANK}, \
	{BLANK, BLANK,  BLANK,  BLANK}  \
}

// J piece
#define J0 { \
	{BLANK,  BLANK, BLANK, BLANK}, \
	{BLUE,   BLUE,  BLUE,  BLANK}, \
	{BLANK,  BLANK, BLUE,  BLANK}, \
	{BLANK,  BLANK, BLANK, BLANK}  \
}
#define J1 { \
	{BLANK, BLUE,  BLANK, BLANK}, \
	{BLANK, BLUE,  BLANK, BLANK}, \
	{BLUE,  BLUE,  BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}
#define J2 { \
	{BLANK, BLANK, BLANK, BLANK}, \
	{BLUE,  BLANK, BLANK, BLANK}, \
	{BLUE,  BLUE,  BLUE,  BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}
#define J3 { \
	{BLANK, BLUE,  BLUE,  BLANK}, \
	{BLANK, BLUE,  BLANK, BLANK}, \
	{BLANK, BLUE,  BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}

// S piece
#define S0 { \
	{BLANK, BLANK, BLANK, BLANK}, \
	{BLANK, GREEN, GREEN, BLANK}, \
	{GREEN, GREEN, BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}
#define S1 { \
	{GREEN, BLANK, BLANK, BLANK}, \
	{GREEN, GREEN, BLANK, BLANK}, \
	{BLANK, GREEN, BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}

// Z piece
#define Z0 { \
	{BLANK, BLANK, BLANK, BLANK}, \
	{RED,   RED,   BLANK, BLANK}, \
	{BLANK, RED,   RED,   BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}
#define Z1 { \
	{BLANK, BLANK, RED,   BLANK}, \
	{BLANK, RED,   RED,   BLANK}, \
	{BLANK, RED,   BLANK, BLANK}, \
	{BLANK, BLANK, BLANK, BLANK}  \
}

// O piece
#define O { \
	{BLANK, BLANK,  BLANK,  BLANK}, \
	{BLANK, YELLOW, YELLOW, BLANK}, \
	{BLANK, YELLOW, YELLOW, BLANK}, \
	{BLANK, BLANK,  BLANK,  BLANK}  \
}

const uint8_t PieceColormaps[7][4][4][4] = {
	{L0, L1, L2, L3}, // L
	{J0, J1, J2, J3}, // J
	{T0, T1, T2, T3}, // T
	{Z0, Z1, Z0, Z1}, // Z
	{O,  O,  O,  O},  // O
	{S0, S1, S0, S1}, // S
	{I0, I1, I0, I1}, // I
};
#else
const uint8_t PieceColormaps[7][4][4][4] = {
    // L
    {{{BLANK, BLANK, BLANK, BLANK},
      {ORANGE, ORANGE, ORANGE, BLANK},
      {ORANGE, BLANK, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{ORANGE, ORANGE, BLANK, BLANK},
      {BLANK, ORANGE, BLANK, BLANK},
      {BLANK, ORANGE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, BLANK, ORANGE, BLANK},
      {ORANGE, ORANGE, ORANGE, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, ORANGE, BLANK, BLANK},
      {BLANK, ORANGE, BLANK, BLANK},
      {BLANK, ORANGE, ORANGE, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // J
    {{{BLANK, BLANK, BLANK, BLANK},
      {BLUE, BLUE, BLUE, BLANK},
      {BLANK, BLANK, BLUE, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLUE, BLANK, BLANK},
      {BLANK, BLUE, BLANK, BLANK},
      {BLUE, BLUE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLUE, BLANK, BLANK, BLANK},
      {BLUE, BLUE, BLUE, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLUE, BLUE, BLANK},
      {BLANK, BLUE, BLANK, BLANK},
      {BLANK, BLUE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // T
    {{{BLANK, BLANK, BLANK, BLANK},
      {PURPLE, PURPLE, PURPLE, BLANK},
      {BLANK, PURPLE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, PURPLE, BLANK, BLANK},
      {PURPLE, PURPLE, BLANK, BLANK},
      {BLANK, PURPLE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, PURPLE, BLANK, BLANK},
      {PURPLE, PURPLE, PURPLE, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, PURPLE, BLANK, BLANK},
      {BLANK, PURPLE, PURPLE, BLANK},
      {BLANK, PURPLE, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // Z
    {{{BLANK, BLANK, BLANK, BLANK},
      {RED, RED, BLANK, BLANK},
      {BLANK, RED, RED, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, RED, BLANK},
      {BLANK, RED, RED, BLANK},
      {BLANK, RED, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {RED, RED, BLANK, BLANK},
      {BLANK, RED, RED, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, RED, BLANK},
      {BLANK, RED, RED, BLANK},
      {BLANK, RED, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // O
    {{{BLANK, BLANK, BLANK, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, YELLOW, YELLOW, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // S
    {{{BLANK, BLANK, BLANK, BLANK},
      {BLANK, GREEN, GREEN, BLANK},
      {GREEN, GREEN, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{GREEN, BLANK, BLANK, BLANK},
      {GREEN, GREEN, BLANK, BLANK},
      {BLANK, GREEN, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {BLANK, GREEN, GREEN, BLANK},
      {GREEN, GREEN, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{GREEN, BLANK, BLANK, BLANK},
      {GREEN, GREEN, BLANK, BLANK},
      {BLANK, GREEN, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}}},
    // I
    {{{BLANK, BLANK, BLANK, BLANK},
      {CYAN, CYAN, CYAN, CYAN},
      {BLANK, BLANK, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK}},
     {{BLANK, BLANK, BLANK, BLANK},
      {CYAN, CYAN, CYAN, CYAN},
      {BLANK, BLANK, BLANK, BLANK},
      {BLANK, BLANK, BLANK, BLANK}},
     {{BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK},
      {BLANK, BLANK, CYAN, BLANK}}},
};
#endif // screw this compiler





#define IMAGES_VIA_DEFINE
#ifdef IMAGES_VIA_DEFINE

#define garbageBlock { \
 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, \
 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, \
 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, \
 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, \
}
#define purpleBlock { \
 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, \
 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, \
 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, \
 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, 0xA254, \
}
#define cyanBlock { \
 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, \
 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, \
 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, \
 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, 0xFE49, \
}
#define orangeBlock { \
 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, \
 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, \
 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, \
 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, 0x23FF, \
}
#define yellowBlock	{ \
 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, \
 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, \
 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, \
 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, 0x079F, \
}
#define blueBlock { \
 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, \
 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, \
 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, \
 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, 0xCA47, \
}
#define greenBlock { \
 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, \
 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, \
 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, \
 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, 0x4D84, \
}
#define redBlock { \
 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, \
 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, \
 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, \
 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, 0x20FD, \
}

const uint16_t SquareBitmaps[8][64] = {
	redBlock,
	orangeBlock,
	yellowBlock,
	greenBlock,
	blueBlock,
	cyanBlock,
	purpleBlock,
	garbageBlock
};

#endif
static uint8_t testRotate(piece_t piece, 
								 uint8_t rot,
								 uint8_t x, uint8_t y,
								 uint8_t matrix[22][10]) 
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

void PieceRotate(piece_t piece, 
								 uint8_t *rot, uint8_t drot,
								 uint8_t *x, uint8_t *y,
								 uint8_t matrix[22][10]) 
{
	// rotate
	uint8_t newRot = (*rot + drot) & 0b11U;
	
	// check for collisions
	if(testRotate(piece, newRot, *x, *y, matrix)) {
		*rot = newRot;
		return;
	}
	
	// special case: LJT no kicks when horizontal
	if(piece <= P_T && (*rot ^ 0b01U)) return;
	
	// try one to the right
	if(testRotate(piece, newRot, *x+1, *y, matrix)) {
		*rot = newRot;
		++*x;
		return;
	}
	
	// try one to the left
	if(testRotate(piece, newRot, *x-1, *y, matrix)) {
		*rot = newRot;
		--*x;
		return;
	}
}

uint32_t Random32(uint8_t gen);

#define BagRandomizer 0
void RandomizeBag(piece_t bag[7]) {
	// bag = {P_L, P_J, P_T, P_Z, P_O, P_S, P_I};
	for(uint8_t i = 0, j, temp; i < 7; i++) {
		j = Random32(BagRandomizer) % (8 - i);
		
		temp = bag[i];
		bag[i] = bag[j];
		bag[j] = temp;
	}
}
