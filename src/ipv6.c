#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include "ipv6.h"
#include "tcp.h"
#include "udp.h"

void parse_ipv6(const unsigned char *packet){
    const struct ipv6_header *ipv6 = (const struct ipv6_header *)packet;

    uint32_t first_word = ntohl(ipv6->version_traffic_flow);

    uint8_t version = (first_word >> 28) & 0x0F;
    uint8_t traffic_class = (first_word >> 20) & 0xFF;
    uint32_t flow_label = first_word & 0xFFFFF;

    uint16_t payload_len = ntohs (ipv6 -> payload_len);
    
    char source_ip[INET6_ADDRSTRLEN];
    char destination_ip[INET6_ADDRSTRLEN];

    inet_ntop(
        AF_INET6,
        ipv6->source,
        source_ip,
        sizeof(source_ip)
    );

    inet_ntop(
        AF_INET6,
        ipv6->destination,
        destination_ip,
        sizeof(destination_ip)
    );

    printf("IPv6 packet\n");
    printf("Version: %u\n", version);
    printf("Traffic Class: %u\n", traffic_class);
    printf("Flow Label: %u\n", flow_label);
    printf("Payload Length: %u bytes\n", payload_len);
    printf("Next Header: %u\n", ipv6->next_header);
    printf("Hop Limit: %u\n", ipv6->hop_limit);
    printf("Source IP: %s\n", source_ip);
    printf("Destination IP: %s\n", destination_ip);

    printf("========================\n");

    if (ipv6->next_header == 6){
        parse_tcp(packet + 40);
    }
    else if (ipv6->next_header == 17){
        parse_udp(packet + 40);
    }
    else {
        printf("Unsupported IPv6 Next Header: %u\n",
               ipv6->next_header);

    }

}