// #include <sys/socket.h>
// #include <linux/if_arp.h>

#include <unistd.h>



// #include <arpa/inet.h>
// #include <sys/socket.h>


#include "arpmodule.h"

int main() {
    struct sockaddr_ll device;
    char *interface = "enp0s25";
    int bytes;

    uint8_t s_mac[6] = {0x90, 0x1b, 0x0e, 0x85, 0x1d, 0x3b};
    // uint8_t d_mac[6] = {121, 121, 121, 121, 121, 121};
    uint8_t s_ip[4] = {192, 168, 0, 134};
    uint8_t d_ip[4] = {192, 168, 0, 108};

    // arp_header areq = ARPRequest(s_mac, s_ip, d_ip);

    uint8_t *arp_req = arpreq(s_mac, s_ip, d_ip);

    // dump_readable_packet(&areq);

    int arp_socket;

    memset (&device, 0, sizeof (device));
    if ((device.sll_ifindex = if_nametoindex(interface)) == 0) {
        perror ("if_nametoindex() failed to obtain interface index ");
        exit (EXIT_FAILURE);
    }
    device.sll_family = AF_PACKET;
    memcpy (device.sll_addr, s_mac, ETH_ALEN);
    device.sll_halen = 6;


    if ((arp_socket = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
        perror ("socket() failed ");
        exit (EXIT_FAILURE);
    }
    // for(int i = 0)
    if ((bytes = sendto (arp_socket, arp_req, sizeof(struct _arp_header), 0, (struct sockaddr *) &device, sizeof (device))) <= 0) {
        perror ("sendto() failed");
        exit (EXIT_FAILURE);
    } 


    // if(arp_socket = socket(AF_NETLINK))

    close(arp_socket);
    free(arp_req);

    printf("sent.\n");
    return 0;
}



uint8_t *arpreq(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip) {

    /* pierwsze co, dodanie naglowka ethernet */
    struct ethhdr eth_hdr;

    /* w ARP mac dest jest adresem broadcast */
    memset(eth_hdr.h_dest, 0xff, ETH_ALEN);

    /* mac src to mac maszyny */
    memcpy(eth_hdr.h_source, src_mac, ETH_ALEN);

    /* proto dla ARP to 0x0806 */
    eth_hdr.h_proto = htons(ETH_P_ARP);
 
    struct _arp_header arphdr = ARPRequest(src_mac, eth_hdr.h_dest, src_ip, dst_ip);     

    // uint8_t *req = malloc(sizeof(struct _arp_header) + sizeof(eth_hdr));


    // memcpy(req, &eth_hdr, sizeof(eth_hdr));
    // memcpy(req + sizeof(eth_hdr), &arphdr, sizeof(arphdr));
    uint8_t *req = malloc(sizeof(struct _arp_header));
    memcpy(req, &arphdr, sizeof(arphdr));
    return req;
}

arp_header ARPRequest(uint8_t src_mac[6], uint8_t dst_mac[6],
                    uint8_t src_ip[4], uint8_t dst_ip[4]) {
    //inicjalizacja pakietu ARP dla ethernetu

    arp_header arp = {
        .eth_type = htons(ETH_P_ARP),
        .htype = htons(ARPHRD_ETHER),
        .hlen = 6,
        .ptype = htons(0x0800),  //IPv4
        .plen = 4,
        .opcode = htons(ARPOP_REQUEST)
    };

    memcpy(arp.eth_shost, src_mac, arp.hlen);
    memcpy(arp.eth_dhost, dst_mac, arp.hlen);

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