#include <stdio.h>
#include <arpa/inet.h>
#include "udp.h"

void parse_udp (const unsigned char *packet){
    const struct udp_header * udp = (const struct udp_header *)packet;
    
    uint16_t udp_source = ntohs(udp->udp_source);
    uint16_t udp_destination = ntohs(udp->udp_destination);
    uint16_t udp_length = ntohs(udp->udp_length);
    uint16_t udp_checksum = ntohs(udp->udp_checksum);

    printf("UDP packet\n");
    printf("Source Port: %u\n", udp_source);
    printf("Destination Port: %u\n", udp_destination);
    printf("Length: %u bytes\n", udp_length);
    printf("Checksum: 0x%04x\n", udp_checksum);

    printf("========================\n");

}