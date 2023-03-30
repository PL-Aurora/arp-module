#include <sys/socket.h>
#include <linux/if_arp.h>

#include <arpa/inet.h> // htons

#include "arpmodule.h"

int main() {
    uint8_t s_mac[6] = {213, 1, 162, 184, 17, 93};
    uint8_t d_mac[6] = {121, 121, 121, 121, 121, 121};
    uint8_t s_ip[6] = {192, 168, 12, 174};
    uint8_t d_ip[6] = {121, 121, 121, 121};

    arp_header areq = ARPRequest(s_mac, d_mac, s_ip, d_ip);


    dump_readable_packet(&areq);

    int arp_socket;

    // if(arp_socket = socket(AF_NETLINK))

    return 0;
}

arp_header ARPRequest(uint8_t src_mac[6], uint8_t dst_mac[6],
                    uint8_t src_ip[4], uint8_t dst_ip[4]) {
    //inicjalizacja pakietu ARP dla ethernetu

    arp_header arp = {
        .htype = htons(ARPHRD_ETHER),
        .hlen = 6,
        .ptype = htons(0x0800),  //IPv4
        .plen = 4,
        .opcode = htons(ARPOP_REQUEST)
    };

    memcpy(arp.src_mac, src_mac, arp.hlen);
    memcpy(arp.dst_mac, dst_mac, arp.hlen);
    memcpy(arp.src_ip, src_ip, arp.plen);
    memcpy(arp.dst_ip, dst_ip, arp.plen);

    return arp;
}

void dump_readable_packet(const arp_header *hdr) {
    uint8_t src_mac_addr[18];
    uint8_t src_ip_addr[16];

    //MAC src
    snprintf(src_mac_addr, sizeof(src_mac_addr), "%02x:%02x:%02x:%02x:%02x:%02x",
    hdr->src_mac[0], hdr->src_mac[1], hdr->src_mac[2], 
    hdr->src_mac[3], hdr->src_mac[4], hdr->src_mac[5]);

    snprintf(src_ip_addr, sizeof(src_ip_addr), "%d.%d.%d.%d",
    hdr->src_ip[0], hdr->src_ip[1], hdr->src_ip[2], hdr->src_ip[3]);

    printf("ARP from: IP=%s, MAC=%s\n", src_ip_addr, src_mac_addr);
}