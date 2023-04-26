#ifndef _ARPSPOOF_H_
#define _ARPSPOOF_H_

#include <pthread.h>

#include "arpmodule.h"

void spoofer(int argc, char *argv[]);

void schedule_queue();

void rng(uint8_t *data, const int min, const int max, const int nums);

void transform_ip(uint8_t *ip, uint32_t ip_decimal);
uint8_t *rand_mac(uint8_t *mac);


#endif //_ARPSPOOF_H_