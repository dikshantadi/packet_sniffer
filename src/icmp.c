#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "icmp.h"

void parse_icmp (const unsigned char *packet){
    const struct icmp_header *icmp = (const struct icmp_header *)packet;

    uint16_t checksum = ntohs(icmp->checksum);

    printf("ICMP packet\n");
    printf("Type: %u\n", icmp->type);
    printf("Code: %u\n", icmp->code);
    printf("Checksum: 0x%04x\n", checksum);

    if (icmp->type == 8 || icmp-> type == 0){
        const struct icmp_echo *echo = (const struct icmp_echo *)(packet + 4);

        uint16_t identifier = ntohs(echo->identifier);
        uint16_t seq_no = ntohs(echo->seq_no);

        if (icmp->type == 8){
            printf ("Message : Echo Request \n");
        }
        else {
            printf("Message: Echo Reply\n");
    } 
        printf("Identifier: %u\n", identifier);
        printf("Sequence Number: %u\n", seq_no);

}
else {
    printf("Unsupported ICMP Type: %u\n", icmp->type);
}

printf("================== \n");
}