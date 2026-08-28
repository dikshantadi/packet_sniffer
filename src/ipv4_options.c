#include <stdio.h>
#include <string.h>
#include "ipv4_options.h"
#include <arpa/inet.h>

void parse_ipv4_options ( const unsigned char *options, uint8_t options_length){
    uint8_t i = 0;

    while (i < options_length){
        uint8_t type = options[i];

        if (type == 0){
            printf("IPv4 Option: End of Option List\n");
            break;
        }

        if (type == 1){
            printf ("IPv4 Options : No operations \n");
            i++;
            continue;
        }

        if (i + 1 >= options_length){
            printf("Malformed IPv4 option: missing length\n");
            break;
        }

        uint8_t length = options[i + 1];

        if (length < 2) {
            printf("Malformed IPv4 option: invalid length %u\n", length);
            break;
        }

        if (i + length > options_length) {
            printf("Malformed IPv4 option: exceeds options area\n");
            break;
        }

        printf("IPv4 Option: Type=%u Length=%u\n", type, length);

        i += length;

    }
}
