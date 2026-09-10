#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
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
    unsigned int packet_size,
    const struct timeval *timestamp
){
    flow->end_time = *timestamp;
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
    uint8_t protocol,
    const struct timeval *timestamp
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

    new_flow->start_time = *timestamp;
    new_flow->end_time = *timestamp;

    return new_flow;
}

void add_flow (
    struct flow **flow_list,
    struct flow *new_flow    
){
    new_flow->next = *flow_list;

    *flow_list = new_flow;    
}

double timeval_diff(
    const struct timeval *end,
    const struct timeval *start
)
{
    return (double)(end->tv_sec - start->tv_sec)
         + (double)(end->tv_usec - start->tv_usec) / 1000000.0;
}

void print_flow(const struct flow *flow_list)
{
    const struct flow *current = flow_list;

    int flow_number = 1;

    printf("\n");
    printf("========== Flow Statistics ==========\n");

    while (current != NULL)
    {
        char source_ip[INET6_ADDRSTRLEN];
        char destination_ip[INET6_ADDRSTRLEN];

        if (current->endpoint_a.ip.version == 4)
        {
            inet_ntop(
                AF_INET,
                &current->endpoint_a.ip.address.ipv4,
                source_ip,
                sizeof(source_ip)
            );

            inet_ntop(
                AF_INET,
                &current->endpoint_b.ip.address.ipv4,
                destination_ip,
                sizeof(destination_ip)
            );
        }
        else
        {
            inet_ntop(
                AF_INET6,
                &current->endpoint_a.ip.address.ipv6,
                source_ip,
                sizeof(source_ip)
            );

            inet_ntop(
                AF_INET6,
                &current->endpoint_b.ip.address.ipv6,
                destination_ip,
                sizeof(destination_ip)
            );
        }

        printf("\nFlow %d\n", flow_number++);
        printf("-------------------------------------\n");

        printf(
            "Protocol    : %s\n",
            current->protocol == 6 ? "TCP" :
            current->protocol == 17 ? "UDP" :
            "Unknown"
        );

        printf(
            "Endpoint A  : %s:%u\n",
            source_ip,
            current->endpoint_a.port
        );

        printf(
            "Endpoint B  : %s:%u\n",
            destination_ip,
            current->endpoint_b.port
        );

        printf(
            "Total Packets : %lu\n",
            current->total_packets
        );

        printf(
            "Total Bytes   : %lu\n",
            current->total_bytes
        );

        printf("\nA -> B\n");

        printf(
            "  Packets : %lu\n",
            current->packets_a_to_b
        );

        printf(
            "  Bytes   : %lu\n",
            current->bytes_a_to_b
        );

        printf("\nB -> A\n");

        printf(
            "  Packets : %lu\n",
            current->packets_b_to_a
        );

        printf(
            "  Bytes   : %lu\n",
            current->bytes_b_to_a
        );

        /*printf("Start Time : %ld.%06ld\n",
            (long)current->start_time.tv_sec,
            (long)current->start_time.tv_usec);

        printf("End Time   : %ld.%06ld\n",
            (long)current->end_time.tv_sec,
            (long)current->end_time.tv_usec);*/
       
        double duration = timeval_diff(
            &current->end_time,
            &current->start_time);

        printf("Duration    : %.6f seconds\n", 
                duration);

            current = current->next;
        
    }

    printf("\n=====================================\n");
}

void free_flow(struct flow *flow_list){
    struct flow *current = flow_list;

    while (current != NULL)
    {
        struct flow *next = current->next;

        free(current);

        current = next;
    }
}