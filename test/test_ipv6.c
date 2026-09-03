#include <stdio.h>
#include <stdint.h>
#include "ipv6_exthdr.h"

int main(void)
{
/*
     * IPv6 Hop-by-Hop header:
     *
     * Byte 0: Next Header = 6 (TCP)
     * Byte 1: Header Ext Len = 0
     * Bytes 2-7: options/padding
     */
    unsigned char packet[] = {
        6, 0,
        0, 8, 0, 0, 0, 0
    };

    struct ipv6_parse_result result =
        parse_ipv6_exthdr(
            packet,
            sizeof(packet),
            44
        );

    printf("\nFinal Next Header: %u\n",
           result.next_header);

    printf("Remaining payload length: %u\n",
           result.payload_length);

    return 0;
}