#include <time.h>
#include <stdlib.h>

#include "arpspoof.h"

void schedule_queue() {
    
}

uint8_t *rand_mac(uint8_t *mac) {
    srand(time(NULL));
    rng(mac, 0, 255, 6);
    return mac;
}

void rng(uint8_t *data, const int min, const int max, const int nums) {
    int nrng = 0;
    for (int i = 0; i < nums; i++) {
        nrng = rand() % (max - min) + min;
        data[i] = nrng;
        printf("%d ", nrng);
    }
}