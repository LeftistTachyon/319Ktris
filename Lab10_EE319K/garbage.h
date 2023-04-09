#ifndef __GARBAGE_H
#define __GARBAGE_H

#include <stdbool.h>
#include <stdint.h>

// adds garbage to the queue
bool offerGarbage(uint8_t lines);

// takes the next item from the garbage queue
uint8_t pollGarbage();

// counters the garbage currently in the queue
uint8_t counterGarbage(uint8_t lines);

// is there anything in the queue?
bool hasGarbage();

// (re)initializes the garbage queue
void initGarbage();

#endif // __GARBAGE_H