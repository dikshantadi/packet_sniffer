#include <stdio.h>
#include "ipv4.h"
#include <arpa/inet.h>

void parse_ipv4(const unsigned char *packet)
{

    const struct ipv4_header *ip = (const struct ipv4_header *)packet;

    uint8_t version = ip->version_ihl >> 4;
    uint8_t ihl = ip->version_ihl & 0x0F;
    uint8_t ttl = ip->ttl;
    uint16_t total_length = ntohs(ip->total_length);
    uint16_t identification = ntohs(ip->identification);
    uint16_t flags_fragment_offset = ntohs(ip->flags_fragment_offset);
    uint8_t protocol = ip->protocol;
    uint16_t checksum = ntohs(ip->checksum);

    printf("IPV4 packet! \n");
    printf("Version: %u\n", version);
    printf("IHL: %u\n", ihl);
    printf("Time to Live : %u\n", ttl);
    printf("Total Length : %u\n", total_length);
    printf("Identification : %u\n", identification);
    printf("Flag Fragment offset: %u\n", flags_fragment_offset);
    printf("Protocol: %u\n", protocol); //useful for next parser selector, 6 = tcp, 17 = udp, 1 = icmp
    printf("Checksum: 0x%04x\n", checksum);


}