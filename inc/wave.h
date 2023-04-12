// wave.h
// Lab 6 Extra credit 2) 
// playing wav files.
//
// For use with the TM4C123
// Sounds for ECE319K Lab 10
// Program written by: put your names here
// 1/2/23
#ifndef __WAVE_h
#define __WAVE_h
#include <stdint.h>
// initialize Wave functionality
void Wave_Init(void);

// start and stop
void Wave_Start();
void Wave_Stop();

// set active channels
void Wave_SetActiveChannels(uint8_t channels);

typedef enum SoundChannel {
	Tri1, Tri2, Tri3, Tri4, Square1, Square2, Square3, Noise
} soundchannel_t;

#define DEFAULT_SOUND
#ifdef DEFAULT_SOUND
// 6-bit sounds, 11.025kHz sampling
#define shootsize 4080
extern const uint8_t shoot[shootsize];
#define invaderkilledsize 3377
extern const uint8_t invaderkilled[invaderkilledsize] ;
#define explosionsize 2000
extern const uint8_t explosion[explosionsize] ;
#define fastinvader1size 982
extern const uint8_t fastinvader1[fastinvader1size];
#define fastinvader2size 1042
extern const uint8_t fastinvader2[fastinvader2size];
#define fastinvader3size 1054
extern const uint8_t fastinvader3[fastinvader3size] ;
#define fastinvader4size 1098
extern const uint8_t fastinvader4[fastinvader4size] ;
#define highpitchsize 1802
extern const uint8_t highpitch[highpitchsize];

//******* Wave_Start ************
// These functions do not output to the DAC. 
// Rather, they set a pointer and counter, and then enables the timer interrupt.
// It starts the sound, and the timer ISR does the output
// feel free to change the parameters
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Wave_Play(const uint8_t *pt, uint32_t count);
// stop wave output
void Wave_Stop(void);
// start playing shoot
void Wave_Shoot(void);
// start playing invaderkilled
void Wave_Killed(void);
// start playing explosion
void Wave_Explosion(void);
// start playing highpitch
void Wave_Highpitch(void);
#endif

#endif
