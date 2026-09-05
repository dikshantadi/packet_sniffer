#ifndef STAT_H
#define STAT_H

#include <stdint.h>

struct capture_stats {
    unsigned long total_packets;
    unsigned long total_captured_bytes;
    unsigned long total_original_bytes;

    double capture_duration;
    
    //Network later protocols
    unsigned long ipv4_packets;
    unsigned long ipv6_packets;
    unsigned long icmp_packets;
    unsigned long icmp6_packets;

    //Transport layer
    unsigned long tcp_packets;
    unsigned long udp_packets;

    //Link layer
    unsigned long arp_packets;
};

void init_capture_stats(struct capture_stats *stats);

void print_capture_stats(const struct capture_stats *stats);


#endif

