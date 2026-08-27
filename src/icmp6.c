#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "icmp6.h"

void parse_icmp6 (const unsigned char *packet){
    const struct icmp6_header *icmp6 = (const struct icmp6_header *)packet;

    uint16_t checksum = ntohs(icmp6->checksum);

    printf("ICMPv6 packet\n");
    printf("Type: %u\n", icmp6->type);
    printf("Code: %u\n", icmp6->code);
    printf("Checksum: 0x%04x\n", checksum);

    if (icmp6->type == 128 || icmp6-> type == 129){
        const struct icmp6_echo *echo = (const struct icmp6_echo *)(packet + 4);

        uint16_t identifier = ntohs(echo->identifier);
        uint16_t seq_no = ntohs(echo->seq_no);

        if (icmp6->type == 128){
            printf ("Message : Echo Request \n");
        }
        else {
            printf("Message: Echo Reply\n");
    } 
        printf("Identifier: %u\n", identifier);
        printf("Sequence Number: %u\n", seq_no);

}
else {
    printf("Unsupported ICMPv6 Type: %u\n", icmp6->type);
}

printf("================== \n");
}