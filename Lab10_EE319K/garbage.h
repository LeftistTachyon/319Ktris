#ifndef __GARBAGE_H
#define __GARBAGE_H

#include <stdbool.h>
#include <stdint.h>

// adds garbage to the queue
bool GQ_OfferGarbage(uint8_t lines);

// takes the next item from the garbage queue
uint8_t GQ_PollGarbage();

// counters the garbage currently in the queue
uint8_t GQ_CounterGarbage(uint8_t lines);

// is there anything in the queue?
bool GQ_HasGarbage();

// (re)initializes the garbage queue
void GQ_InitGarbage();

// gets the well for the next section of garbage
uint8_t GQ_GetGarbageWell();

#endif // __GARBAGE_H