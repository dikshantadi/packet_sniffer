#ifndef ARP_H
#define ARP_H

#include <stdint.h>

/*
 * ARP is used for IPv4 address resolution.
 * IPv6 uses Neighbor Discovery Protocol (NDP),
 * which is implemented using ICMPv6.
 */


struct arp_header {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_length;
    uint8_t protocol_length;
    uint16_t operation;

    uint8_t sender_mac[6];
    uint8_t sender_ip[4];

    uint8_t target_mac[6];
    uint8_t target_ip[4];

};

void parse_arp (const unsigned char *packet);

#endif