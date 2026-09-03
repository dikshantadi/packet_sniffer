#include <stdio.h>
#include <arpa/inet.h>
#include "ethernet.h"
#include "ipv4.h"
#include "ipv6.h"
#include "arp.h"
#include <stdint.h>

void print_mac(const unsigned char *mac)
{
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0],
           mac[1],
           mac[2],
           mac[3],
           mac[4],
           mac[5]);
}

int parse_ethernet(const unsigned char *packet, uint32_t packet_length)
{
    const struct ethernet_header *eth =
        (const struct ethernet_header *)packet;

    unsigned short ether_type = ntohs(eth->ether_type);

    printf("Destination MAC: ");
    print_mac(eth->destination);
    printf("\n");

    printf("Source MAC: ");
    print_mac(eth->source);
    printf("\n");

    printf("EtherType: 0x%04x\n", ether_type);
    printf("========================\n");

    if (ether_type == 0x0800) {
        parse_ipv4(packet + 14);
        return 1;
    }
    else if (ether_type == 0x86DD) {
        parse_ipv6(packet + 14, packet_length - 14);
    }
    else if (ether_type == 0x0806){
        parse_arp(packet + 14);
    }
    else {
        printf("Unknown/unsupported EtherType\n");
    }

    return 0;
}