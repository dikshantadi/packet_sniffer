#include <stdio.h>
#include <arpa/inet.h>
#include "tcp.h"

void parse_tcp(const unsigned char *packet){
    const struct tcp_header *tcp = (const struct tcp_header *)packet;

    uint16_t source_port = ntohs(tcp->source_port);
    uint16_t destination_port = ntohs(tcp->destination_port);

    uint32_t seq_no = ntohl(tcp->seq_no);
    uint32_t ack_no = ntohl(tcp->ack_no);

    //uint8_t data_offset = ntohs (tcp->data_offset_reversed);
    //uint8_t flags 

    printf("TCP packet \n");
    printf("Source Port : %u \n", source_port);
    printf("Destination port : %u \n", destination_port);
    printf("Acknowledgement Number : %u \n", ack_no);
    printf("Sequence no: %u \n", seq_no);
}
