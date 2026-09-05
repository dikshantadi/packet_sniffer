#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>
#include "stat.h"

struct ethernet_header {
    unsigned char destination[6];
    unsigned char source[6];
    uint16_t ether_type;
};

int parse_ethernet(
    const unsigned char *packet, 
    uint32_t packet_length, 
    struct capture_stats *stats);

#endif