#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include "ipv6_exthdr.h"


#define IPV6_HOP_BY_HOP   0
#define IPV6_ROUTING      43
#define IPV6_FRAGMENT     44
#define IPV6_DESTINATION  60
#define IPV6_AH           51
#define IPV6_ESP          50
#define IPV6_NO_NEXT      59


struct ipv6_parse_result parse_ipv6_exthdr(
    const unsigned char *extension,
    uint16_t length,
    uint8_t next_header
)
{
    struct ipv6_parse_result result = {0};

    result.next_header = next_header;
    result.payload = extension;
    result.payload_length = length;

    while (1)
    {
        /*
         * Hop-by-Hop, Routing and Destination Options
         */
        if (next_header == IPV6_HOP_BY_HOP ||
            next_header == IPV6_ROUTING ||
            next_header == IPV6_DESTINATION)
        {
            if (length < 2)
            {
                printf("Malformed IPv6 extension header\n");
                return result;
            }

            uint8_t next = extension[0];
            uint8_t hdr_ext_len = extension[1];

            uint16_t header_length =
                (hdr_ext_len + 1) * 8;

            if (header_length > length)
            {
                printf("Malformed IPv6 extension header: "
                       "header exceeds packet\n");
                return result;
            }

            printf("IPv6 Extension Header\n");
            printf("Type: %u\n", next_header);
            printf("Length: %u bytes\n", header_length);
            printf("Next Header: %u\n", next);
            printf("========================\n");

            extension += header_length;
            length -= header_length;
            next_header = next;

            continue;
        }


        /*
         * Fragment Header
         */
        if (next_header == IPV6_FRAGMENT)
        {
            if (length < 8)
            {
                printf("Malformed IPv6 Fragment Header\n");
                return result;
            }

            uint8_t next = extension[0];

            uint16_t fragment_field;

            memcpy(&fragment_field,
                   extension + 2,
                   sizeof(fragment_field));

            fragment_field = ntohs(fragment_field);

            uint16_t fragment_offset =
                (fragment_field >> 3) & 0x1FFF;

            int more_fragments =
                fragment_field & 0x01;

            uint32_t identification;

            memcpy(&identification,
                   extension + 4,
                   sizeof(identification));

            identification = ntohl(identification);

            printf("IPv6 Fragment Header\n");
            printf("Next Header: %u\n", next);
            printf("Fragment Offset: %u\n",
                   fragment_offset);
            printf("More Fragments: %s\n",
                   more_fragments ? "Yes" : "No");
            printf("Identification: %u\n",
                   identification);
            printf("========================\n");

            result.fragmented = 1;
            result.fragment_offset = fragment_offset;
            result.more_fragments = more_fragments;

            extension += 8;
            length -= 8;
            next_header = next;

            /*
             * A non-zero fragment offset means this
             * fragment does not begin with the transport
             * header.
             */
            if (fragment_offset != 0)
            {
                result.next_header = next_header;
                result.payload = extension;
                result.payload_length = length;

                return result;
            }

            continue;
        }


        /*
         * Authentication Header
         */
        if (next_header == IPV6_AH)
        {
            if (length < 2)
            {
                printf("Malformed IPv6 AH header\n");
                return result;
            }

            uint8_t next = extension[0];
            uint8_t payload_len = extension[1];

            /*
             * AH length is:
             * (Payload Len + 2) * 4
             */
            uint16_t header_length =
                (payload_len + 2) * 4;

            if (header_length > length)
            {
                printf("Malformed IPv6 AH header\n");
                return result;
            }

            printf("IPv6 Authentication Header (AH)\n");
            printf("Length: %u bytes\n", header_length);
            printf("Next Header: %u\n", next);
            printf("========================\n");

            extension += header_length;
            length -= header_length;
            next_header = next;

            continue;
        }


        /*
         * ESP
         *
         * We can identify ESP, but cannot simply walk
         * through it like the other extension headers
         * because its encrypted payload has no usable
         * Next Header field available to this parser.
         */
        if (next_header == IPV6_ESP)
        {
            printf("IPv6 ESP Header\n");
            printf("Encrypted payload - stopping parser\n");
            printf("========================\n");

            result.next_header = IPV6_ESP;
            result.payload = extension;
            result.payload_length = length;

            return result;
        }


        /*
         * No Next Header
         */
        if (next_header == IPV6_NO_NEXT)
        {
            printf("IPv6: No Next Header\n");
            printf("========================\n");

            result.next_header = IPV6_NO_NEXT;
            result.payload = extension;
            result.payload_length = length;

            return result;
        }


        /*
         * We reached the transport protocol
         * or an unsupported Next Header.
         */
        result.next_header = next_header;
        result.payload = extension;
        result.payload_length = length;

        return result;
    }
}