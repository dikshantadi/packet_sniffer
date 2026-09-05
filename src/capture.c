#include <stdio.h>
#include <pcap.h>
#include <string.h>

#include "capture.h"
#include "ethernet.h"
#include "stat.h"

void list_interfaces(void)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return;
    }

    int i = 0;

    for (pcap_if_t *device = alldevs;
         device != NULL;
         device = device->next)
    {
        printf("%d. %s\n", ++i, device->name);
    }

    pcap_freealldevs(alldevs);
}

void open_capture(const char *device, struct capture_stats *stats)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    struct bpf_program filter_program;
    char filter_exp[256] = "";  // Important for now 

    pcap_t *handle = pcap_open_live(
        device,
        BUFSIZ,
        1,
        1000,
        errbuf
    );

    if (handle == NULL)
    {
        fprintf(stderr,
                "Couldn't open device %s: %s\n",
                device,
                errbuf);
        return;
    }

    printf("Successfully opened: %s\n", device);

    printf("Enter BPF Filter (press Enter for none): ");
    fgets(filter_exp, sizeof(filter_exp), stdin);

    filter_exp[strcspn(filter_exp, "\n")] = '\0';
    if (strlen (filter_exp) > 0){
    if (pcap_compile(
            handle,
            &filter_program,
            filter_exp,
            1,
            PCAP_NETMASK_UNKNOWN
        ) == -1)
    {
        fprintf(stderr,
                "Couldn't parse filter %s: %s\n",
                filter_exp,
                pcap_geterr(handle));

        pcap_close(handle);
        return;
    }

    if (pcap_setfilter(handle, &filter_program) == -1)
    {
        fprintf(stderr,
                "Couldn't install filter %s: %s\n",
                filter_exp,
                pcap_geterr(handle));

        pcap_freecode(&filter_program);
        pcap_close(handle);
        return;
    }

    pcap_freecode(&filter_program);

    printf("Filter applied: %s\n", filter_exp);
}
 else {
    printf("No filter applied. Capturing all packets \n");
 }

    struct pcap_pkthdr *header;
    const u_char *packet;
    int packet_count = 0;

    while (packet_count < 10)
    {
        int result = pcap_next_ex(handle, &header, &packet);

        if (result == 1)
        {
            stats->total_packets++;
            stats->total_captured_bytes += header->caplen;
            stats->total_original_bytes += header->len;

            printf("\nPacket %d\n", packet_count + 1);
            printf("========================\n");

            printf("Captured length: %u bytes\n", header->caplen);
            printf("Original length: %u bytes\n", header->len);

            parse_ethernet(packet, header->caplen, stats);

            packet_count++;
        }
    }

    pcap_close(handle);
}