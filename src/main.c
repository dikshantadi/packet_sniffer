#include <stdio.h>

#include "capture.h"

int main(void)
{
    printf("Packet Analyzer\n");
    printf("================\n");

    list_interfaces();

    open_capture("wlp0s20f3");
    

    return 0;
}