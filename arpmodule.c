#include <unistd.h>
#include <linux/if_arp.h>

#include "arpmodule.h"

int main() {
    uint8_t s_mac[6] = {213, 1, 162, 184, 17, 93};
    uint8_t d_mac[6] = {121, 121, 121, 121, 121, 121};
    uint8_t s_ip[6] = {192, 168, 12, 174};
    uint8_t d_ip[6] = {121, 121, 121, 121};

    arp_header areq = ARPRequest(s_mac, d_mac, s_ip, d_ip);

    char mac[20];
    char ip[20]; 

snprintf(mac, sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",
         areq.src_mac[0], areq.src_mac[1], areq.src_mac[2], 
         areq.src_mac[3], areq.src_mac[4], areq.src_mac[5]);

snprintf(ip, sizeof(ip), "%d.%d.%d.%d",
         areq.src_ip[0], areq.src_ip[1], areq.src_ip[2], 
         areq.src_ip[3]);

    printf("arp:\nhtype: %d, ptype: %d, mac_src: %s, ip_src: %s\n", 
    areq.htype, areq.ptype, mac, ip);
    return 0;
}

arp_header ARPRequest(uint8_t src_mac[6], uint8_t dst_mac[6],
                    uint8_t src_ip[4], uint8_t dst_ip[4]) {
    //inicjalizacja pakietu ARP dla ethernetu

    arp_header arp = {
        .htype = ARPHRD_ETHER,
        .hlen = 6,
        .ptype = 0x0800,  //IPv4
        .plen = 4,
        .opcode = ARPOP_REQUEST
    };
    /* memset(arp.src_mac, 0, arp.hlen);
    memset(arp.dst_mac, 0, arp.hlen);
    memset(arp.src_ip, 0, arp.plen);
    memset(arp.dst_ip, 0, arp.plen); */

    memcpy(arp.src_mac, src_mac, arp.hlen);
    memcpy(arp.dst_mac, dst_mac, arp.hlen);
    memcpy(arp.src_ip, src_ip, arp.plen);
    memcpy(arp.dst_ip, dst_ip, arp.plen);

    return arp;
}