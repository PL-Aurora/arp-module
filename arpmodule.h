#ifndef _ARPMODULE_H_
#define _ARPMODULE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include <stdint.h>

// // #include <linux/if.h>
// #include <linux/if_ether.h>

// #include <net/if.h> //if_nametoindex

#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_ARP = 0x0806
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>

#include <linux/if_arp.h>



struct _arp_header {
    uint8_t eth_dhost[ETH_ALEN];
    uint8_t eth_shost[ETH_ALEN];
    uint16_t eth_type;

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

uint8_t *arpreq(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip);

void dump_readable_packet(const arp_header *hdr);

#endif