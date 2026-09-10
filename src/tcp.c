#include <stdio.h>
#include <arpa/inet.h>
#include "tcp.h"
#include "tcp_options.h"
#include "flow.h"
#include <sys/time.h>

void parse_tcp(
    const unsigned char *packet,
    struct flow **flow_list,
    struct flow_endpoint source,
    struct flow_endpoint destination,
    unsigned int packet_size,
    const struct timeval *timestamp    
){
    const struct tcp_header *tcp = (const struct tcp_header *)packet;

    uint16_t source_port = ntohs(tcp->source_port);
    uint16_t destination_port = ntohs(tcp->destination_port);

    source.port = source_port;
    destination.port = destination_port;

    struct flow *flow = find_flow(
        *flow_list,
        &source,
        &destination,
        6
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
        6,
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

    uint32_t seq_no = ntohl(tcp->seq_no);
    uint32_t ack_no = ntohl(tcp->ack_no);

    uint8_t data_offset = tcp->data_offset_reversed >> 4;
    uint8_t tcp_header = data_offset * 4; //*4 because Data Offset is measured in 32-bit words, and 32 bits = 4 bytes 

    uint8_t flags = tcp->flag;
    uint8_t urg = (flags >> 5) & 1;
    uint8_t ack = (flags >> 4) & 1;
    uint8_t psh = (flags >> 3) & 1;
    uint8_t rst = (flags >> 2) & 1;
    uint8_t syn = (flags >> 1) & 1;
    uint8_t fin = flags & 1;

    uint16_t window_size = ntohs(tcp->window_size);
    uint16_t tcp_check = ntohs (tcp -> tcp_check);
    uint16_t urgent_pointer = ntohs (tcp -> urgent_pointer);

    uint8_t options_length = tcp_header - 20;

    printf("TCP packet \n");
    printf("Source Port : %u \n", source_port);
    printf("Destination port : %u \n", destination_port);
    printf("Sequence no: %u \n", seq_no);
    printf("Acknowledgement Number : %u \n", ack_no);
    printf("Data Offset: %u (32-bit words)\n", data_offset);
    printf("TCP Header Length: %u bytes\n", tcp_header);
    printf("Flags:\n");
    printf("  URG: %u\n", urg);
    printf("  ACK: %u\n", ack);
    printf("  PSH: %u\n", psh);
    printf("  RST: %u\n", rst);
    printf("  SYN: %u\n", syn);
    printf("  FIN: %u\n", fin);
    printf("window size : %u\n", window_size);
    printf("Checksum : %u\n", tcp_check);
    printf("Urgent Pointer : %u\n", urgent_pointer);
    printf("TCP Options Length: %u bytes\n", options_length);

    if (options_length > 0) {
    const unsigned char *options = packet + 20;

    parse_tcp_options(options, options_length);
    }

    printf("======================== \n");
    
}
