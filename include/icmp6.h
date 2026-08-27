#ifndef ICMP6_H
#define ICMP6_H
#include <stdint.h>

struct icmp6_header{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;

};

struct icmp6_echo {
    uint16_t identifier;
    uint16_t seq_no;
};

void parse_icmp6(const unsigned char *packet);
#endif