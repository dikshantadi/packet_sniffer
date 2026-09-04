#include <stdio.h>
#include <pcap.h>

#include "capture.h"
#include "ethernet.h"

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

void open_capture(const char *device)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    struct bpf_program filter_program;
    char filter_exp[] = "tcp";

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

    struct pcap_pkthdr *header;
    const u_char *packet;
    int packet_count = 0;

    while (packet_count < 10)
    {
        int result = pcap_next_ex(handle, &header, &packet);

        if (result == 1)
        {
            printf("\nPacket %d\n", packet_count + 1);
            printf("========================\n");

            printf("Captured length: %u bytes\n", header->caplen);
            printf("Original length: %u bytes\n", header->len);

            parse_ethernet(packet, header->caplen);

            packet_count++;
        }
    }

    pcap_close(handle);
}