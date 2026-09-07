#include <stdio.h>

#include "capture.h"
#include "stat.h"
#include "flow.h"

int main(void)
{
    printf("Packet Analyzer\n");
    printf("================\n");

    struct capture_stats stats;
    struct flow *flow_list = NULL;
    init_capture_stats(&stats);

    list_interfaces();

    open_capture("wlp0s20f3", &stats, &flow_list);

    print_capture_stats(&stats);
    print_flow(flow_list);
    free_flow(flow_list);

    return 0;
}