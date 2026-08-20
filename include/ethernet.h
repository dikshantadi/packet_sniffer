#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

struct ethernet_header {
    unsigned char destination[6];
    unsigned char source[6];
    uint16_t ether_type;
};

void parse_ethernet(const unsigned char *packet);

#endif