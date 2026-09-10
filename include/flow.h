#ifndef FLOW_H
#define FLOW_H

#include <stdint.h>
#include <netinet/in.h>
#include <sys/time.h>


struct ip_address
{
    uint8_t version;

    union
    {
        struct in_addr ipv4;
        struct in6_addr ipv6;
    } address;
};


struct flow_endpoint
{
    struct ip_address ip;
    uint16_t port;
};


enum flow_direction
{
    FLOW_A_TO_B,
    FLOW_B_TO_A
};


struct flow
{
    struct flow_endpoint endpoint_a;
    struct flow_endpoint endpoint_b;

    uint8_t protocol;
    
    struct timeval start_time;
    struct timeval end_time;

    unsigned long total_packets;
    unsigned long total_bytes;

    unsigned long packets_a_to_b;
    unsigned long packets_b_to_a;

    unsigned long bytes_a_to_b;
    unsigned long bytes_b_to_a;

    struct flow *next;
};

void init_flow(struct flow *flow);

void set_flow(
    struct flow *flow,
    struct flow_endpoint endpoint_a,
    struct flow_endpoint endpoint_b,
    uint8_t protocol
);

void update_flow(
    struct flow *flow,
    enum flow_direction direction,
    unsigned int packet_size,
    const struct timeval *timestamp
);


int get_flow_direction(
    const struct flow *flow,
    const struct flow_endpoint *source
);


int same_ip(
    const struct ip_address *ip1,
    const struct ip_address *ip2
);


int flow_matches(
    const struct flow *flow,
    const struct flow_endpoint *source,
    const struct flow_endpoint *destination,
    uint8_t protocol
);


struct flow *create_flow(
    const struct flow_endpoint *endpoint_a,
    const struct flow_endpoint *endpoint_b,
    uint8_t protocol,
    const struct timeval *timestamp
);


struct flow *find_flow(
    struct flow *flow_list,
    const struct flow_endpoint *source,
    const struct flow_endpoint *destination,
    uint8_t protocol
);



void add_flow(
    struct flow **flow_list,
    struct flow *new_flow
);

void print_flow(const struct flow *flow_list);

void free_flow(struct flow *flow_list);

#endif
