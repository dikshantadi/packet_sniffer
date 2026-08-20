#ifndef IPV4_H
#define IPV4_H
#include <stdint.h>

struct ipv4_header {
    uint8_t version_ihl;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t source_ip;
    uint32_t destination_ip;
};

void parse_ipv4(const unsigned char *packet);

#endif