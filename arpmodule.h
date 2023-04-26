#ifndef _ARPMODULE_H_
#define _ARPMODULE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// #include <stdint.h>

// // #include <linux/if.h>
// #include <linux/if_ether.h>

// #include <net/if.h> //if_nametoindex

/* za duzo plikow naglowkowych, trzeba zrobic porzadek */

#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()

#include <arpa/inet.h>        // inet_pton() and inet_ntop()

#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_ARP = 0x0806
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)

#define ARPHRD_ETHER 1

#define	ARPOP_REQUEST 1
#define	ARPOP_REPLY	2


struct arp_header {
    uint16_t htype; //hardware type, for ethernet is 1
    uint16_t ptype; //protocol of higher layer
    uint8_t hlen; //hardware address len, for ether 6 (MAC addr)
    uint8_t plen; //protocol length, for IPv4 4
    uint16_t opcode; //operation type 1 - request, 2 - reply

    uint8_t src_mac[ETH_ALEN];
    uint8_t src_ip[4];
    uint8_t dst_mac[ETH_ALEN];
    uint8_t dst_ip[4];
};


struct ethhdr stdethhdr(uint8_t *src_mac);
struct arp_header stdarphdr(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip);

uint8_t *arpreq(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip);


void dump_readable_packet(const struct arp_header *hdr);

#endif