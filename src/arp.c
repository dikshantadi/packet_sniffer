#include <stdio.h>
#include <arpa/inet.h>
#include "arp.h"
#include <stdint.h>

void parse_arp(const unsigned char *packet){
    const struct arp_header *arp = (const struct arp_header *)packet;

    uint16_t hardware_type = ntohs(arp -> hardware_type);
    uint16_t protocol_type = ntohs(arp -> protocol_type);
    uint16_t operation = ntohs(arp->operation);
    uint8_t hardware_length = arp->hardware_length;
    uint8_t protocol_length = arp->protocol_length;

    printf("ARP packet \n");

    printf("Hardware Type: %u\n", hardware_type);
    printf("Protocol Type: 0x%04x\n", protocol_type);
    printf("Hardware Length: %u\n", hardware_length);
    printf("Protocol Length: %u\n", protocol_length);
    printf("Operation : %u\n", operation);

    printf("Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp->sender_mac[0],
           arp->sender_mac[1],
           arp->sender_mac[2],
           arp->sender_mac[3],
           arp->sender_mac[4],
           arp->sender_mac[5]);

    printf("Sender IP: %u.%u.%u.%u\n",
           arp->sender_ip[0],
           arp->sender_ip[1],
           arp->sender_ip[2],
           arp->sender_ip[3]);

    printf("Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp->target_mac[0],
           arp->target_mac[1],
           arp->target_mac[2],
           arp->target_mac[3],
           arp->target_mac[4],
           arp->target_mac[5]);

    printf("Target IP: %u.%u.%u.%u\n",
           arp->target_ip[0],
           arp->target_ip[1],
           arp->target_ip[2],
           arp->target_ip[3]);

    printf("========================\n");



}

