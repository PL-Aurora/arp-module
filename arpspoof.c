#include <time.h>
#include <stdlib.h>

#include "arpspoof.h"

void spoofer(int argc, char *argv[]) {
    if(getuid != 0) {
        printf("Uruchom jako root, wychodzenie z programu...\n");
        exit(EXIT_FAILURE);
    }

    uint8_t victim_ip[4];
    memset(victim_ip, 0, sizeof(victim_ip));

    if(argc != 1) {
        struct sockaddr_in sa;
        if(!inet_pton(AF_INET, argv[1], &(sa.sin_addr))) {
            printf("Niewlasciwy docelowy adres IP. Uruchom program z poprawnym adresem IP, konczenie...\n");
            exit(EXIT_FAILURE);
        }
        transform_ip(victim_ip, sa.sin_addr.s_addr);
    }

    
}

void transform_ip(uint8_t *ip, uint32_t ip_decimal) {
    ip[0] = ip_decimal & 0xff;
    ip[1] = (ip_decimal >> 8) & 0xff;
    ip[2] = (ip_decimal >> 16) & 0xff;
    ip[3] = (ip_decimal >> 24) & 0xff;
}

void schedule_queue() {
    uint8_t victim_ip[4];

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