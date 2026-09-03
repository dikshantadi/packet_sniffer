#ifndef IPV6_H
#define IPV6_H

#include <stdint.h>

struct ipv6_header
{
    uint32_t version_traffic_flow;

    uint16_t payload_len;

    uint8_t next_header;
    uint8_t hop_limit;

    unsigned char source[16];
    unsigned char destination[16];
};

void parse_ipv6(
    const unsigned char *packet,
    uint16_t packet_length
);

#endif