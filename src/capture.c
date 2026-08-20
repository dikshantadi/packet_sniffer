#include <stdio.h>
#include <pcap.h>

#include "capture.h"

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

void open_capture (const char *device){
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle;

    handle = pcap_open_live(device,
         BUFSIZ,
        1,
        1000,
        errbuf);
    if (handle == NULL) {
	fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
	return;
}
    printf("Successfully opened: %s\n", device);

    pcap_close(handle);
   
}