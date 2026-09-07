#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flow.h"

void init_flow(struct flow *flow){
    flow->total_packets = 0;
    flow->total_bytes = 0;

    flow->packets_a_to_b = 0;
    flow->packets_b_to_a = 0;

    flow->bytes_a_to_b = 0;
    flow->bytes_b_to_a = 0;

    flow->next = NULL;
}

void set_flow ( 
    struct flow *flow,     
    struct flow_endpoint endpoint_a,
    struct flow_endpoint endpoint_b,
    uint8_t protocol ){
        flow->endpoint_a = endpoint_a;
        flow->endpoint_b = endpoint_b;
        flow->protocol = protocol;
}

void update_flow(
    struct flow *flow,
    enum flow_direction direction,
    unsigned int packet_size
){
    flow -> total_packets++;
    flow->total_bytes += packet_size;

    if (direction == FLOW_A_TO_B){
        flow->packets_a_to_b++;
        flow->bytes_a_to_b += packet_size;
    }
    else if (direction == FLOW_B_TO_A)
    {
        flow->packets_b_to_a++;
        flow->bytes_b_to_a += packet_size;
    }
}

int get_flow_direction(
    const struct flow *flow,
    const struct flow_endpoint *source
)
{
    if (same_ip(
            &source->ip,
            &flow->endpoint_a.ip
        ) &&
        source->port == flow->endpoint_a.port)
    {
        return FLOW_A_TO_B;
    }

    if (same_ip(
            &source->ip,
            &flow->endpoint_b.ip
        ) &&
        source->port == flow->endpoint_b.port)
    {
        return FLOW_B_TO_A;
    }

    return -1;
}

int same_ip(
    const struct ip_address *ip1,
    const struct ip_address *ip2   
){
    if (ip1->version != ip2->version){
        return 0;
    }
    if (ip1->version == 4){
        return memcmp(
            &ip1->address.ipv4,
            &ip2->address.ipv4,
            sizeof(struct in_addr) 
        ) == 0;
    }

    if (ip1->version == 6){
        return memcmp(
            &ip1->address.ipv6,
            &ip2->address.ipv6,
            sizeof(struct in6_addr)  
        ) == 0;
    }
    return 0;
}

int flow_matches(
    const struct flow *flow,
    const struct flow_endpoint *source,
    const struct flow_endpoint *destination,
    uint8_t protocol
)
{
    if (flow->protocol != protocol)
    {
        return 0;
    }

    if (same_ip(
            &source->ip,
            &flow->endpoint_a.ip
        ) &&
        source->port == flow->endpoint_a.port &&
        same_ip(
            &destination->ip,
            &flow->endpoint_b.ip
        ) &&
        destination->port == flow->endpoint_b.port)
    {
        return 1;
    }

    if (same_ip(
            &source->ip,
            &flow->endpoint_b.ip
        ) &&
        source->port == flow->endpoint_b.port &&
        same_ip(
            &destination->ip,
            &flow->endpoint_a.ip
        ) &&
        destination->port == flow->endpoint_a.port)
    {
        return 1;
    }

    return 0;
}

struct flow *find_flow(
    struct flow *flow_list,
    const struct flow_endpoint *source,
    const struct flow_endpoint *destination,
    uint8_t protocol   
)
{
    struct flow *current = flow_list;

    while (current != NULL)
    {
        if (flow_matches(
                current,
                source,
                destination,
                protocol
            ))
        {
            return current;
        }

        current = current->next;
    }

    return NULL;    
}

struct flow *create_flow(
    const struct flow_endpoint *endpoint_a,
    const struct flow_endpoint *endpoint_b,
    uint8_t protocol
)
{
    struct flow *new_flow = malloc(sizeof(struct flow));

    if (new_flow == NULL)
    {
        return NULL;
    }

    init_flow(new_flow);

    set_flow(
        new_flow,
        *endpoint_a,
        *endpoint_b,
        protocol
    );

    return new_flow;
}

void add_flow (
    struct flow **flow_list,
    struct flow *new_flow    
){
    new_flow->next = *flow_list;

    *flow_list = new_flow;    
}