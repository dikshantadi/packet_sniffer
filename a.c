#include <stdio.h>
#include <pcap.h>

int main(void)
{
    printf("Packet analyzer starting!\n");
    printf("libpcap: %s\n", pcap_lib_version());

    return 0;
}