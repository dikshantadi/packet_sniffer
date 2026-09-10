#include <stdio.h>
#include <arpa/inet.h>
#include "udp.h"
#include <sys/time.h>

void parse_udp(
    const unsigned char *packet,
    struct flow **flow_list,
    struct flow_endpoint source,
    struct flow_endpoint destination,
    unsigned int packet_size,
    const struct timeval *timestamp
)
{
    const struct udp_header *udp =
        (const struct udp_header *)packet;

    uint16_t udp_source =
        ntohs(udp->udp_source);

    uint16_t udp_destination =
        ntohs(udp->udp_destination);

    source.port = udp_source;
    destination.port = udp_destination;

    struct flow *flow = find_flow(
        *flow_list,
        &source,
        &destination,
        17
    );

    if (flow != NULL)
    {
        int direction = get_flow_direction(
            flow,
            &source
        );

        update_flow(
            flow,
            direction,
            packet_size,
            timestamp
        );
    }
    else
    {
        flow = create_flow(
            &source,
            &destination,
            17,
            timestamp
        );

        if (flow != NULL)
        {
            add_flow(
                flow_list,
                flow
            );

            update_flow(
                flow,
                FLOW_A_TO_B,
                packet_size,
                timestamp
            );
        }
    }

    uint16_t udp_length =
        ntohs(udp->udp_length);

    uint16_t udp_checksum =
        ntohs(udp->udp_checksum);

    printf("UDP packet\n");
    printf("Source Port: %u\n", udp_source);
    printf("Destination Port: %u\n", udp_destination);
    printf("Length: %u bytes\n", udp_length);
    printf("Checksum: 0x%04x\n", udp_checksum);

    printf("========================\n");
}