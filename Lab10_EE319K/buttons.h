#include <stdbool.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"


//Button Connections
//PE0 = sDropPressed
//PE1 = hDropPressed
//PE2 = rotateCWPressed
//PE3 = rotateCCWPressed
//PE4 = holdPressed

//Button Flags
extern bool sDropPressed;
extern bool hDropPressed;
extern bool rotateCWPressed;
extern bool rotateCCWPressed;
extern bool holdPressed;

//Initalizes GPIO Interrupts on PortE
void Button_Init(void);
