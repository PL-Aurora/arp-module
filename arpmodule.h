#ifndef _ARPMODULE_H_
#define _ARPMODULE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>


struct _arp_header {
    uint16_t htype; //hardware type, for ethernet is 1
    uint16_t ptype; //protocol of higher layer
    uint8_t hlen; //hardware address len, for ether 6 (MAC addr)
    uint8_t plen; //protocol length, for IPv4 4
    uint16_t opcode; //operation type 1 - request, 2 - reply

    uint8_t src_mac[6];
    uint8_t dst_mac[6];
    uint8_t src_ip[4];
    uint8_t dst_ip[4];
};

typedef struct _arp_header arp_header;

arp_header ARPRequest(uint8_t src_mac[6], uint8_t dst_mac[6],
                    uint8_t src_ip[4], uint8_t dst_ip[4]);
arp_header ARPResponse();

#endif