#include <stdio.h>
#include "ipv4.h"

void parse_ipv4(const unsigned char *packet)
{

    const struct ipv4_header *ip = (const struct ipv4_header *)packet;

    uint8_t version = ip->version_ihl >> 4;
    uint8_t ihl = ip->version_ihl & 0x0F;

    printf("IPV4 packet! \n");
    printf("Version: %u\n", version);
    printf("IHL: %u\n", ihl);
}