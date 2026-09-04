#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

#include "ipv6.h"
#include "ipv6_exthdr.h"

#include "tcp.h"
#include "udp.h"
#include "icmp6.h"


#define IPV6_HEADER_LENGTH 40
#define TCP_PROTOCOL   6
#define UDP_PROTOCOL   17
#define ICMPV6_PROTOCOL 58
#define IPV6_NO_NEXT 59


void parse_ipv6(const unsigned char *packet, uint16_t packet_length)
{
    if (packet_length < IPV6_HEADER_LENGTH)
    {
        printf("Malformed IPv6 packet: header too short\n");
        return;
    }

    const struct ipv6_header *ipv6 =
        (const struct ipv6_header *)packet;


    /*
     * First 32 bits:
     *
     * Version        = 4 bits
     * Traffic Class  = 8 bits
     * Flow Label     = 20 bits
     */

    uint32_t first_word =
        ntohl(ipv6->version_traffic_flow);

    uint8_t version =
        (first_word >> 28) & 0x0F;

    uint8_t traffic_class =
        (first_word >> 20) & 0xFF;

    uint32_t flow_label =
        first_word & 0xFFFFF;


    uint16_t payload_length =
        ntohs(ipv6->payload_len);


    char source_ip[INET6_ADDRSTRLEN];
    char destination_ip[INET6_ADDRSTRLEN];


    inet_ntop(
        AF_INET6,
        ipv6->source,
        source_ip,
        sizeof(source_ip)
    );

    inet_ntop(
        AF_INET6,
        ipv6->destination,
        destination_ip,
        sizeof(destination_ip)
    );


    printf("IPv6 packet\n");

    printf("Version: %u\n", version);
    printf("Traffic Class: %u\n", traffic_class);
    printf("Flow Label: %u\n", flow_label);

    printf("Payload Length: %u bytes\n",
           payload_length);

    printf("Next Header: %u\n",
           ipv6->next_header);

    printf("Hop Limit: %u\n",
           ipv6->hop_limit);

    printf("Source IP: %s\n",
           source_ip);

    printf("Destination IP: %s\n",
           destination_ip);

    printf("========================\n");


    /*
     * The IPv6 fixed header is always 40 bytes.
     */
    const unsigned char *payload =
        packet + IPV6_HEADER_LENGTH;


    /*
     * Actual captured payload length.
     *
     * This protects us from reading past
     * the captured packet.
     */
    uint16_t available_length =
        packet_length - IPV6_HEADER_LENGTH;


    /*
     * The IPv6 Payload Length tells us how much
     * data IPv6 says follows the fixed header.
     */
    if (payload_length < available_length)
    {
        available_length = payload_length;
    }


    /*
     * Walk IPv6 extension headers.
     *
     * If there are no extension headers,
     * this simply returns the original pointer.
     */
    struct ipv6_parse_result result =
        parse_ipv6_exthdr(
            payload,
            available_length,
            ipv6->next_header
        );


    uint8_t final_protocol =
        result.next_header;


    const unsigned char *final_payload =
        result.payload;


    /*uint16_t final_length =
        result.payload_length;
*/

    /*
     * Fragment handling.
     *
     * If this is a non-first fragment, the
     * TCP/UDP/ICMPv6 header is not here.
     */
    if (result.fragmented &&
        result.fragment_offset != 0)
    {
        printf("Non-first IPv6 fragment\n");
        printf("Transport header not present\n");

        return;
    }


    /*
     * No Next Header
     */
    if (final_protocol == IPV6_NO_NEXT)
    {
        return;
    }


    /*
     * TCP
     */
    if (final_protocol == TCP_PROTOCOL)
    {
        parse_tcp(final_payload);
    }


    /*
     * UDP
     */
    else if (final_protocol == UDP_PROTOCOL)
    {
        parse_udp(final_payload);
    }


    /*
     * ICMPv6
     */
    else if (final_protocol == ICMPV6_PROTOCOL)
    {
        parse_icmp6(final_payload);
    }


    /*
     * ESP
     */
    else if (final_protocol == 50)
    {
        printf("IPv6 payload: ESP\n");
    }


    /*
     * AH
     */
    else if (final_protocol == 51)
    {
        printf("IPv6 payload: AH\n");
    }


    /*
     * Unknown / unsupported protocol
     */
    else
    {
        printf("Unsupported IPv6 Next Header: %u\n",
               final_protocol);
    }
}