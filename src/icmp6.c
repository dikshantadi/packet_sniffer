#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "icmp6.h"

void parse_icmp6(const unsigned char *packet)
{
    const struct icmp6_header *icmp6 =
        (const struct icmp6_header *)packet;

    uint16_t checksum = ntohs(icmp6->checksum);

    printf("ICMPv6 packet\n");
    printf("Type: %u\n", icmp6->type);
    printf("Code: %u\n", icmp6->code);
    printf("Checksum: 0x%04x\n", checksum);

    if (icmp6->type == 128 || icmp6->type == 129) {

        const struct icmp6_echo *echo =
            (const struct icmp6_echo *)(packet + 4);

        uint16_t identifier = ntohs(echo->identifier);
        uint16_t seq_no = ntohs(echo->seq_no);

        if (icmp6->type == 128) {
            printf("Message: Echo Request\n");
        }
        else {
            printf("Message: Echo Reply\n");
        }

        printf("Identifier: %u\n", identifier);
        printf("Sequence Number: %u\n", seq_no);
    }

    else if (icmp6->type == 135) {

        const struct ndp_neighbour_solicitation *ns =
            (const struct ndp_neighbour_solicitation *)(packet + 4);

        char target_ip[INET6_ADDRSTRLEN];

        inet_ntop(
            AF_INET6,
            ns->target_address,
            target_ip,
            sizeof(target_ip)
        );

        printf("Message: Neighbor Solicitation\n");
        printf("Target Address: %s\n", target_ip);

        const struct ndp_option *option = (const struct ndp_option *)(packet + 24);

        printf("Option Type: %u\n", option->type);
        printf("Option Length: %u\n", option->length);
        
        if (option->type == 1 || option->type == 2) {
    printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        option->data[0],
        option->data[1],
        option->data[2],
        option->data[3],
        option->data[4],
        option->data[5]);
}
else {
    printf("Unsupported NDP Option: %u\n", option->type);
}

    }

    else if (icmp6->type == 136) {

    const struct ndp_neighbour_advertisement *na =
        (const struct ndp_neighbour_advertisement *)(packet + 4);

    char target_ip[INET6_ADDRSTRLEN];

    inet_ntop(
        AF_INET6,
        na->target_address,
        target_ip,
        sizeof(target_ip)
    );

    uint32_t flags = ntohl(na->flags_reserved);

    uint8_t router = (flags >> 31) & 1;
    uint8_t solicited = (flags >> 30) & 1;
    uint8_t override = (flags >> 29) & 1;


    printf("Message: Neighbor Advertisement\n");
    printf("Router: %u\n", router);
    printf("Solicited: %u\n", solicited);
    printf("Override: %u\n", override);
    printf("Target Address: %s\n", target_ip);

    const struct ndp_option *option = (const struct ndp_option *)(packet + 24);


    printf("Option Type: %u\n", option->type);
    printf("Option Length: %u\n", option->length);


    if (option->type == 1 || option->type == 2) {
    printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        option->data[0],
        option->data[1],
        option->data[2],
        option->data[3],
        option->data[4],
        option->data[5]);
}
else {
    printf("Unsupported NDP Option: %u\n", option->type);
}
}

    else {
        printf("Unsupported ICMPv6 Type: %u\n", icmp6->type);
    }



    printf("==================\n");
}