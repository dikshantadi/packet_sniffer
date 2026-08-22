#ifndef UDP_H
#define UDP_H

#include <stdint.h>

struct udp_header{
    uint16_t udp_source;
    uint16_t udp_destination;
    uint16_t udp_length;
    uint16_t udp_checksum;
};

void parse_udp(const unsigned char *packet);

#endif