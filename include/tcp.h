#ifndef TCP_H
#define TCP_H

#include <stdint.h>
#include "flow.h"

struct tcp_header {
    uint16_t source_port;
    uint16_t destination_port;
    uint32_t seq_no;
    uint32_t ack_no;
    uint8_t data_offset_reversed;
    uint8_t flag;
    uint16_t window_size;
    uint16_t tcp_check;
    uint16_t urgent_pointer;
    uint8_t option_length;
};

void parse_tcp(
    const unsigned char *packet,
    struct flow **flow_list,
    struct flow_endpoint source,
    struct flow_endpoint destination,
    unsigned int packet_size,
    const struct timeval *timestamp
);

#endif