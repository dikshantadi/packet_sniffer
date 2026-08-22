#include <stdio.h>
#include "ipv4.h"
#include <arpa/inet.h>
#include "tcp.h"
#include "udp.h"

void parse_ipv4(const unsigned char *packet)
{

    const struct ipv4_header *ip = (const struct ipv4_header *)packet;

    uint8_t version = ip->version_ihl >> 4;
    uint8_t ihl = ip->version_ihl & 0x0F;
    uint8_t ttl = ip->ttl;
    uint16_t total_length = ntohs(ip->total_length);
    uint16_t identification = ntohs(ip->identification);
    uint16_t flags_fragment_offset = ntohs(ip->flags_fragment_offset);
    uint8_t flags = (flags_fragment_offset >> 13) & 0x07;
    uint16_t fragment_offset = flags_fragment_offset & 0x1FFF;
    uint8_t protocol = ip->protocol;
    uint16_t checksum = ntohs(ip->checksum);
    char source_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->source_ip, source_ip, sizeof(source_ip));
    char destination_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->destination_ip, destination_ip, sizeof(destination_ip));

    printf("IPV4 packet! \n");
    printf("Version: %u\n", version);
    printf("IHL: %u\n", ihl);
    printf("Time to Live : %u\n", ttl);
    printf("Total Length : %u\n", total_length);
    printf("Identification : %u\n", identification);
    printf("Flag : %u\n", flags);
    printf("Fragment Offset : %u\n", fragment_offset);
    printf("Protocol: %u\n", protocol); //useful for next parser selector, 6 = tcp, 17 = udp, 1 = icmp
    printf("Checksum: 0x%04x\n", checksum);
    printf("Source IP: %s\n", source_ip);
    printf("Destination IP: %s\n", destination_ip);
    printf("======================== \n");

    if (protocol == 6){
        parse_tcp(packet + ihl * 4);
    }
    else if (protocol == 17){
        parse_udp(packet + ihl * 4);
    }
}