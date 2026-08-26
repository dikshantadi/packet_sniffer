#ifndef ICMP_H
#define ICMP_H
#include <stdint.h>

struct icmp_header{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;

};

struct icmp_echo {
    uint16_t identifier;
    uint16_t seq_no;
};

void parse_icmp(const unsigned char *packet);
#endif