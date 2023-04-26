#ifndef _ARPSPOOF_H_
#define _ARPSPOOF_H_

#include <pthread.h>

#include "arpmodule.h"

void schedule_queue();

void rng(uint8_t *data, const int min, const int max, const int nums);

uint8_t *rand_mac(uint8_t *mac);


#endif //_ARPSPOOF_H_