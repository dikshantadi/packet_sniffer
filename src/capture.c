#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "capture.h"
#include "ethernet.h"
#include "stat.h"


void list_interfaces(void)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,
                "Couldn't find devices: %s\n",
                errbuf);
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


void open_capture(
    const char *device,
    struct capture_stats *stats
)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    // Capture duration
    char duration_input[32];
    char *endptr;
    long duration;

    // BPF filter 
    struct bpf_program filter_program;
    char filter_exp[256] = "";

    printf("Capture duration (seconds): ");

    if (fgets(
            duration_input,
            sizeof(duration_input),
            stdin
        ) == NULL)
    {
        fprintf(stderr,
                "Failed to read capture duration.\n");
        return;
    }

    duration = strtol(
        duration_input,
        &endptr,
        10
    );

    if (endptr == duration_input || duration <= 0)
    {
        fprintf(stderr,
                "Invalid capture duration.\n");
        return;
    }

    //Open capture devices
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

    //Ask user for BPF filter
    printf("Enter BPF Filter (press Enter for none): ");

    if (fgets(
            filter_exp,
            sizeof(filter_exp),
            stdin
        ) == NULL)
    {
        fprintf(stderr,
                "Failed to read filter.\n");

        pcap_close(handle);
        return;
    }

    filter_exp[strcspn(filter_exp, "\n")] = '\0';


     //Apply BPF filter if provided
    if (strlen(filter_exp) > 0)
    {
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

        if (pcap_setfilter(
                handle,
                &filter_program
            ) == -1)
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

        printf("Filter applied: %s\n",
               filter_exp);
    }
    else
    {
        printf("No filter applied. "
               "Capturing all packets.\n");
    }


    struct pcap_pkthdr *header;
    const u_char *packet;

    struct timeval start_time;

    gettimeofday(
        &start_time,
        NULL
    );


    while (1)
    {
        struct timeval current_time;

        gettimeofday(
            &current_time,
            NULL
        );


        
        //Calculate elapsed time
        double elapsed =
            (current_time.tv_sec - start_time.tv_sec) +
            (current_time.tv_usec - start_time.tv_usec)
                / 1000000.0;



        //Stop when duration expires
        if (elapsed >= (double)duration)
        {
            break;
        }


 
        //Get next packet
        int result = pcap_next_ex(
            handle,
            &header,
            &packet
        );


        if (result == 1)
        {
          
             //Update capture statistics
            stats->total_packets++;

            stats->total_captured_bytes +=
                header->caplen;

            stats->total_original_bytes +=
                header->len;



            // Display packet information
            printf("\nPacket %lu\n",
                   stats->total_packets);

            printf("========================\n");

            printf("Captured length: %u bytes\n",
                   header->caplen);

            printf("Original length: %u bytes\n",
                   header->len);

                //Parse packets
            parse_ethernet(
                packet,
                header->caplen,
                stats
            );
        }
        else if (result == 0)
        {
             //Read timeout.
            continue;
        }
        else if (result == -1)
        {
            fprintf(stderr,
                    "Capture error: %s\n",
                    pcap_geterr(handle));

            break;
        }
        else if (result == -2)
        {
            printf("Capture ended\n");
            break;
        }
    }

    struct timeval end_time;
    gettimeofday (&end_time, NULL);

    stats->capture_duration = (end_time.tv_sec - start_time.tv_sec) 
    + (end_time.tv_usec - start_time.tv_usec)/ 1000000.0;


    pcap_close(handle);
}