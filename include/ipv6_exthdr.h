#ifndef IPV6_EXTHDR_H
#define IPV6_EXTHDR_H

#include <stdint.h>

struct ipv6_parse_result {
    uint8_t next_header;

    const unsigned char *payload;
    uint16_t payload_length;

    int fragmented;
    uint16_t fragment_offset;
    int more_fragments;
};

struct ipv6_parse_result parse_ipv6_exthdr(
    const unsigned char *extension,
    uint16_t length,
    uint8_t next_header
);

#endif