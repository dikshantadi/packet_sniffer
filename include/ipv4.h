#ifndef IPV4_H
#define IPV4_H
#include <stdint.h>
#include "stat.h"

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
    uint8_t ipv4_header_length;
    uint8_t options_length;
};

void parse_ipv4(
    const unsigned char *packet,
    struct capture_stats *stat
);

#endif