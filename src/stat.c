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

    stats->capture_duration = 0;

    stats->min_packet_size = 0;
    stats->max_packet_size = 0;

}

void print_capture_stats (const struct capture_stats *stats){

    double packets_per_second = 0.0;
    double bytes_per_second = 0.0;
    double average_packet_size = 0.0;

    double ipv4_percentage = 0.0;
    double ipv6_percentage = 0.0;
    double arp_percentage = 0.0;
    double tcp_percentage = 0.0;
    double udp_percentage = 0.0;
    double icmp_percentage = 0.0;
    double icmp6_percentage = 0.0;

    if (stats->total_packets > 0){
        average_packet_size = 
        (double)stats -> total_captured_bytes / stats -> total_packets;

        ipv4_percentage =
            ((double)stats->ipv4_packets /
            stats->total_packets) * 100.0;

        ipv6_percentage =
            ((double)stats->ipv6_packets /
            stats->total_packets) * 100.0;

        arp_percentage =
            ((double)stats->arp_packets /
            stats->total_packets) * 100.0;

        tcp_percentage =
            ((double)stats->tcp_packets /
            stats->total_packets) * 100.0;

        udp_percentage =
            ((double)stats->udp_packets /
            stats->total_packets) * 100.0;

        icmp_percentage =
            ((double)stats->icmp_packets /
            stats->total_packets) * 100.0;

        icmp6_percentage =
            ((double)stats->icmp6_packets /
            stats->total_packets) * 100.0;
    }

    if (stats->capture_duration > 0.0){
    
    packets_per_second = 
        stats->total_packets / stats->capture_duration;
    
    bytes_per_second =
        stats->total_captured_bytes / stats ->capture_duration;
    }



    printf ("\n");
    printf("========== Capture Statistics ==========\n");

    printf("Capture Duration : %.2f seconds \n", stats->capture_duration);
    printf ("\n");


    printf("Total Packets : %lu \n", stats->total_packets);
    printf("Captured bytes : %lu \n", stats->total_captured_bytes);
    printf("Original bytes : %lu \n", stats->total_original_bytes);

    printf("\n");

    printf("Transport Layer Statistics \n");
    printf("TCP packets captured : %lu (%.2f%%) \n", stats->tcp_packets, tcp_percentage);
    printf("UDP packets captured : %lu (%.2f%%) \n", stats->udp_packets, udp_percentage);
    
    printf("\n");

    printf("Network Layer Statistics \n");
    printf("Ipv4 packets Captured : %lu (%.2f%%)\n", stats->ipv4_packets, ipv4_percentage);
    printf("Ipv6 packets captured : %lu (%.2f%%) \n", stats->ipv6_packets, ipv6_percentage);
    printf("Icmp packets captured : %lu (%.2f%%) \n", stats->icmp_packets, icmp_percentage);
    printf("Icmpv6 packets captured : %lu (%.2f%%) \n", stats->icmp6_packets, icmp6_percentage);

    printf("\n");
    printf("Link Layer Statistics \n");
    printf("ARP packets Captured : %lu (%.2f%%)\n", stats->arp_packets, arp_percentage);

    printf("\n");
    printf("Packet Rate : %.2f packets/sec \n", packets_per_second);
    printf("Data Rate : %.2f bytes/sec \n", bytes_per_second);

    printf("\n");
    printf("Minimum Packet size : %u bytes \n", stats ->min_packet_size);
    printf("Maximum Packet size : %u bytes \n", stats ->max_packet_size);
    printf("Average Packet size : %.2f bytes \n", average_packet_size);

    printf("=========================================\n");
}