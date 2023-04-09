#ifndef __PIECES_H

#include <stdint.h>

// color definitions
#define BLANK  0x00
#define RED    0x01
#define ORANGE 0x02
#define YELLOW 0x03
#define GREEN  0x04
#define BLUE   0x05
#define CYAN   0x06
#define PURPLE 0x07
#define GREY   0x08

// piece definitions
typedef enum Piece {
	P_L, P_J, P_T, P_Z, P_O, P_S, P_I
} piece_t;

// piece images
// 7 pieces, 4 rotations, 4x4 colormap
const uint8_t PieceColormaps[7][4][4][4];
// the bitmaps for the individual squares
const uint16_t SquareBitmaps[8][64];

// functions:
// rotate a piece
void PieceRotate(piece_t piece, 
								 uint8_t *rot, 
								 uint8_t drot,
								 uint8_t *x,
								 uint8_t *y,
								 uint8_t matrix[22][10]);

// piece queue functionality
// number of piece previews
#define PIECE_PREVIEWS 3
// init piece queue
void PQ_Init();
// get a piece
piece_t PQ_PollPiece();
// get a piece preview
piece_t PQ_Preview(uint8_t index);
#endif // __PIECES_H