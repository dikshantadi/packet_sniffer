#include <stdio.h>
#include "stat.h"

void init_capture_stats (struct capture_stats *stats){
    stats->total_packets = 0;
    stats->total_captured_bytes = 0;
    stats->total_original_bytes = 0;

    stats->ipv4_packets = 0;
    stats->ipv6_packets = 0;
    stats->icmp_packets = 0;
    stats->icmp6_packets = 0;

    stats->tcp_packets = 0;
    stats->udp_packets = 0;

    stats->arp_packets = 0;

}

void print_capture_stats (const struct capture_stats *stats){
    printf ("\n");
    printf("========== Capture Statistics ==========\n");

    printf("Total Packets : %lu \n", stats->total_packets);
    printf("Captured bytes : %lu \n", stats->total_captured_bytes);
    printf("Original bytes : %lu \n", stats->total_original_bytes);

    printf("\n");

    printf("Transport Layer Statistics \n");
    printf("TCP packets captured : %lu \n", stats->tcp_packets);
    printf("UDP packets captured : %lu \n", stats->udp_packets);
    
    printf("\n");

    printf("Network Layer Statistics \n");
    printf("Ipv4 packets Captured : %lu \n", stats->ipv4_packets);
    printf("Ipv6 packets captured : %lu \n", stats->ipv6_packets);
    printf("Icmp packets captured : %lu \n", stats->icmp_packets);
    printf("Icmpv6 packets captured : %lu \n", stats->icmp6_packets);

    printf("\n");
    printf("Link Layer Statistics \n");
    printf("ARP packets Captured : %lu \n", stats->arp_packets);


    printf("=========================================\n");
}