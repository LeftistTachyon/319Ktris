#include <stdbool.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"


//Button Connections
//PE0 =
//PE1 =
//PE2 =
//PE3 = 
//PE4 =

//Button Flags
bool sDropPressed;
bool hDropPressed;
bool rotateCWPressed;
bool rotateCCWPressed;
bool holdPressed;

//Initalizes GPIO Interrupts on PortE
void Button_Init(void);