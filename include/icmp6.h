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

struct ndp_neighbour_solicitation {
    uint32_t reserved;
    uint8_t target_address[16];
};

struct ndp_neighbour_advertisement {
    uint32_t flags_reserved;
    uint8_t target_address[16];
};

struct ndp_option {
    uint8_t type;
    uint8_t length;
    uint8_t data[6];
};

void parse_icmp6(const unsigned char *packet);
#endif