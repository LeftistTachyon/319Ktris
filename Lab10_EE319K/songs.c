#include "songs.h"

#define HELPER_NOTES
#ifdef HELPER_NOTES
#define C0 2697
#define Cs0 2546
#define Db0 2546
#define D0 2403
#define Ds0 2267
#define Eb0 2267
#define E0 2141
#define F0 2020
#define Fs0 1907
#define Gb0 1907
#define G0 1800
#define Gs0 1699
#define Ab0 1699
#define A0 1604
#define As0 1513
#define Bb0 1513
#define B0 1429
#define C1 1349
#define Cs1 1273
#define Db1 1273
#define D1 1201
#define Ds1 1134
#define Eb1 1134
#define E1 1070
#define F1 1010
#define Fs1 954
#define Gb1 954
#define G1 900
#define Gs1 850
#define Ab1 850
#define A1 802
#define As1 757
#define Bb1 757
#define B1 714
#define C2 674
#define Cs2 636
#define Db2 636
#define D2 601
#define Ds2 567
#define Eb2 567
#define E2 535
#define F2 505
#define Fs2 477
#define Gb2 477
#define G2 450
#define Gs2 425
#define Ab2 425
#define A2 401
#define As2 378
#define Bb2 378
#define B2 357
#define C3 337
#define Cs3 318
#define Db3 318
#define D3 300
#define Ds3 283
#define Eb3 283
#define E3 268
#define F3 253
#define Fs3 238
#define Gb3 238
#define G3 225
#define Gs3 212
#define Ab3 212
#define A3 200
#define As3 189
#define Bb3 189
#define B3 179
#define C4 169
#define Cs4 159
#define Db4 159
#define D4 150
#define Ds4 142
#define Eb4 142
#define E4 134
#define F4 126
#define Fs4 119
#define Gb4 119
#define G4 113
#define Gs4 106
#define Ab4 106
#define A4 100
#define As4 95
#define Bb4 95
#define B4 89
#define C5 84
#define Cs5 80
#define Db5 80
#define D5 75
#define Ds5 71
#define Eb5 71
#define E5 67
#define F5 63
#define Fs5 60
#define Gb5 60
#define G5 56
#define Gs5 53
#define Ab5 53
#define A5 50
#define As5 47
#define Bb5 47
#define B5 45
#define C6 42
#define Cs6 40
#define Db6 40
#define D6 38
#define Ds6 35
#define Eb6 35
#define E6 33
#define F6 32
#define Fs6 30
#define Gb6 30
#define G6 28
#define Gs6 27
#define Ab6 27
#define A6 25
#define As6 24
#define Bb6 24
#define B6 22
#define C7 21
#define Cs7 20
#define Db7 20
#define D7 19
#define Ds7 18
#define Eb7 18
#define E7 17
#define F7 16
#define Fs7 15
#define Gb7 15
#define G7 14
#define Gs7 13
#define Ab7 13
#define A7 13
#define As7 12
#define Bb7 12
#define B7 11
#define C8 11
#define Cs8 10
#define Db8 10
#define D8 9
#define Ds8 9
#define Eb8 9
#define E8 8
#define F8 8
#define Fs8 7
#define Gb8 7
#define G8 7
#define Gs8 7
#define Ab8 7
#define A8 6
#define As8 6
#define Bb8 6
#define B8 6
#endif

const song_t octave = {
	.prescale = 44100,
	.numInsts = 3,
	.numNotes = 2,
	.notes = {
		{
			.tones = {A4, E4, 0, A3, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, A4, E4, A3, 0},
			.delay = 2
		}
	}
};
// Tri1, Tri2, Tri3, Tri4, Square1, Square2, Square3, Noise
const song_t sauls_nokia = {
	.prescale = 3868,
	.numInsts = 4,
	.numNotes = 76,
	.notes = {
		{
			.tones = {0, 0, 0, 0, E5, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, D5, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, Fs4, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, Gs4, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, Cs5, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, B4, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, D4, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, E4, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, B4, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, A4, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {0, 0, 0, 0, Cs4, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, E4, 0, 0, 0},
			.delay = 4
		},
		// Amaj
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4 - 1, E4 - 1, Cs4 - 1, A3 - 1, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4 + 2, E4 + 2, Cs4 + 2, A3 + 2, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {A4 + 4, E4 + 4, Cs4 + 4, A3 + 4, 0, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {A4 + 2, E4 + 2, Cs4 + 2, A3 + 2, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 9
		},
		// slid trio
		{
			.tones = {G4, D4, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {G4 - 3, D4 - 4, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4, E4, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		// eighth note run
		{
			.tones = {Cs5, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {A4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {E4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 4
		},
		// Cmaj
		{
			.tones = {C4, E4, G4, C5, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {C4 - 1, E4 - 1, G4 - 1, C5 - 1, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {C4, E4, G4, C5, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {C4 + 2, E4 + 2, G4 + 2, C5 + 2, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {C4, E4, G4, C5, 0, 0, 0, 0},
			.delay = 15
		},
		// more stuff
		{
			.tones = {D4, F4, A4, E5, 0, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {D4, F4, A4, D5, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {0, 0, 0, D5, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {0, 0, 0, C5 + 4, 0, 0, 0, 0},
			.delay = 1,
		},
		{
			.tones = {0, 0, 0, C5 + 2, 0, 0, 0, 0},
			.delay = 1,
		},
		{
			.tones = {0, 0, 0, C5, 0, 0, 0, 0},
			.delay = 4,
		},
		// Amaj
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4 - 1, E4 - 1, Cs4 - 1, A3 - 1, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {A4 + 2, E4 + 2, Cs4 + 2, A3 + 2, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {A4 + 4, E4 + 4, Cs4 + 4, A3 + 4, 0, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {A4 + 2, E4 + 2, Cs4 + 2, A3 + 2, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {A4, E4, Cs4, A3, 0, 0, 0, 0},
			.delay = 9
		},
		// slide up
		{
			.tones = {E4 - 4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {E4 - 2, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {E4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {Cs5, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {E4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {G4 - 4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {G4 - 2, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {G4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		// E, E3
		{
			.tones = {E3, 0, 0, 0, 0, 0, 0, 0},
			.delay = 8
		},
		{
			.tones = {E3, Gs3, 0, 0, 0, 0, 0, 0},
			.delay = 4
		},
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 4
		},
		// raked
		{
			.tones = {G3, C4, E4, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {0, 0, E4, 0, 0, 0, 0, 0},
			.delay = 3
		},
		{
			.tones = {Eb4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {D4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {Cs4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 2
		},
		{
			.tones = {Eb3, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {Eb3, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {C4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {D4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 3
		},
		{
			.tones = {Gs2, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {B3 - 3, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		}, 
		{
			.tones = {C4 + 3, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {C4, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
		{
			.tones = {0, 0, 0, 0, 0, 0, 0, 0},
			.delay = 1
		},
	}
};

