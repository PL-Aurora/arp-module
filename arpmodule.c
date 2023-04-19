// #include <sys/socket.h>
// #include <linux/if_arp.h>

#include <unistd.h>

// #include <arpa/inet.h>
// #include <sys/socket.h>


#include "arpmodule.h"



int main() {
    struct sockaddr_ll device;
    char *interface = "enp0s3";
    int bytes;

    uint8_t s_mac[6] = {0x90, 0x1b, 0x0e, 0x85, 0x1d, 0x3b};  // mac 1
    // uint8_t d_mac[6] = {121, 121, 121, 121, 121, 121};
    uint8_t s_ip[4] = {192, 168, 0, 134};
    uint8_t d_ip[4] = {192, 168, 0, 1};

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
    if ((bytes = sendto (arp_socket, arp_req, sizeof(struct arp_header) + sizeof(struct ethhdr),
        0, (struct sockaddr *) &device, sizeof (device))) <= 0) {
        perror ("sendto() failed");
        exit (EXIT_FAILURE);
    } 


    // if(arp_socket = socket(AF_NETLINK))

    close(arp_socket);
    free(arp_req);

    printf("sent.\n");
    return 0;
}

struct ethhdr stdethhdr(uint8_t *src_mac) {
    struct ethhdr hdr;
    /* w ARP mac dest jest adresem broadcast */
    memset(hdr.h_dest, 0xff, ETH_ALEN);

    /* mac src to mac maszyny */
    memcpy(hdr.h_source, src_mac, ETH_ALEN);

    /* proto dla ARP to 0x0806 */
    hdr.h_proto = htons(ETH_P_ARP);
    return hdr;
}

struct arp_header stdarphdr(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip) {
    struct arp_header ahdr;

    /* htype dla ethernetu to 1 */
    ahdr.htype = htons(ARPHRD_ETHER);
    ahdr.hlen = ETH_ALEN;

    /* proto dla ramki ARP to IPv4 (0x0800) */
    ahdr.ptype = htons(0x0800);
    ahdr.plen = 4;

    /* arp request = 1, response = 2 */
    ahdr.opcode = htons(ARPOP_REQUEST);

    memcpy(ahdr.src_mac, src_mac, ahdr.hlen);
    memcpy(ahdr.src_ip, src_ip, ahdr.plen);

    memset(ahdr.dst_mac, 0xff, ahdr.hlen);
    memcpy(ahdr.dst_ip, dst_ip, ahdr.plen);

    return ahdr;
}


uint8_t *arpreq(uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip) {
    struct ethhdr eth_hdr;
    struct arp_header ahdr;

    /* pierwsze co, dodanie naglowka ethernet */
    eth_hdr = stdethhdr(src_mac);
 
    /* stworzenie naglowka ARP */
    ahdr = stdarphdr(src_mac, src_ip, dst_ip);

    uint8_t *req = malloc(sizeof(struct arp_header) + sizeof(struct ethhdr));

    /* skopiowanie struktur bo bufora do wyslania */
    memcpy(req, &eth_hdr, sizeof(struct ethhdr));
    memcpy(req + 14, &ahdr, sizeof(struct arp_header));
    
    return req;
}

void dump_readable_packet(const struct arp_header *hdr) {
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