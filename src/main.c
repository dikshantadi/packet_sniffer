#include <stdio.h>

#include "capture.h"
#include "stat.h"

int main(void)
{
    printf("Packet Analyzer\n");
    printf("================\n");

    struct capture_stats stats;
    init_capture_stats(&stats);

    list_interfaces();

    open_capture("wlp0s20f3", &stats);

    print_capture_stats(&stats);

    return 0;
}