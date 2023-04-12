#include <stdint.h>
#include <stdbool.h>
#include "../inc/wave.h"
#include "pieces.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

typedef enum {English, Spanish} Language_t; 


//Sounds Stuff
void Wave_SoundTick(uint8_t channels);
void Wave_SetChannel(soundchannel_t channel, int16_t data);


//Input Variables
int8_t sliderInput;
bool DO_HARDDROP;


//Game Functions
void GameLoop(); //Main Update Method
void setInputs();
void clearInputs();