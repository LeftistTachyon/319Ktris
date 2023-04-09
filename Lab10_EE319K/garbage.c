#include "garbage.h"

static uint8_t deque[32];
static uint8_t start, end;

// adds garbage to the queue
bool GQ_OfferGarbage(uint8_t lines) {
	if(((start + 1) & 0x1F) == end) return false;
	
	deque[start] = lines;
	start = (start + 1) & 0x1F;
	return true;
}

// takes the next item from the garbage queue
uint8_t GQ_PollGarbage() {
	if(start == end) return 0;
	
	uint8_t output = deque[end];
	end = (end + 1) & 0x1F;
	return output;
}

// counters the garbage currently in the queue
uint8_t GQ_CounterGarbage(uint8_t lines) {
	uint8_t countered;
	while(lines > 0 && start != end) {
		countered = deque[start] - lines;
		
		if(countered <= 0) lines = -countered;
		else {
			deque[start] = countered;
			return 0;
		}
		
		start = (start - 1) & 0x1F;
	}
	
	return lines;
}

// is there anything in the queue?
bool GQ_HasGarbage() {
	return start != end;
}

// clears all garbage from the queue
void GQ_InitGarbage() {
	start = end = 0;
}

uint32_t Random32(uint8_t gen);
// gets the well for the next section of garbage
#define GarbageRandomizer 1
uint8_t GQ_GetGarbageWell() {
	return Random32(GarbageRandomizer) % 10;
}
