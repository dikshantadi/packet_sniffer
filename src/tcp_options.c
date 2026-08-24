#include <stdio.h>
#include "tcp_options.h"

void parse_tcp_options ( const unsigned char *options, uint8_t options_length){
    uint8_t i = 0;

    while (i < options_length){
        uint8_t kind = options[i];
        if (kind == 0) {
            printf("  EOL\n");
            break;
        }

        if (kind == 1) {
            printf("  NOP\n");
            i++;
            continue;
        }
        
        if (i + 1 >= options_length) {
            printf("  Malformed option: missing length\n");
            break;
        }

        uint8_t length = options[i + 1];

        if (length < 2) {
         printf("  Malformed option: invalid length %u\n", length);
            break;
        }

        if (i + length > options_length) {
            printf("  Malformed option: extends beyond option area\n");
        break;
            }
        printf("  Option Kind: %u, Length: %u\n", kind, length);

        i = i + length;
    }
}