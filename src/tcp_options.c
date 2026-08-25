#include <stdio.h>
#include <string.h>
#include "tcp_options.h"
#include <arpa/inet.h>

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

        switch (kind){
            case 2: {
                if (length != 4){
                    printf ("Malformed MSS option \n");
                    break;
                }

                uint16_t mss;

                memcpy(&mss, &options[i + 2], sizeof(mss));

                mss = ntohs(mss);
                printf (" MSS : %u bytes \n", mss);
                break;
            }
            case 3: {
                if (length != 3){
                    printf ("Malformed window Scale option \n");
                    break;
                }

                uint8_t winscale;

                memcpy (&winscale, &options[i + 2], sizeof(winscale));
                printf(" Window scale : %u \n ", winscale);

                break;
                }

            case 4 : {
                if (length != 2){
                    printf ("Malformed Selective Ack option \n ");
                    break;
                }
                printf("    SACK Permitted\n");
                break;

            }
            case 5 : {
                printf ("Selective Acknowledgement \n");
                break;
            }
            case 8 : {
                if (length != 10){
                    printf ("Malformed Timestamp Option \n");
                    break;
                }
                printf("Timestamp Option \n");

                uint32_t tsval;
                uint32_t tsecr;

                memcpy(&tsval, &options[i + 2], sizeof(tsval));
                memcpy(&tsecr, &options[i + 6], sizeof(tsecr));

                tsval = ntohl(tsval);
                tsecr = ntohl(tsecr);

                printf (" TSval : %u \n", tsval);
                printf (" TSecr : %u \n", tsecr);
                break;
            }

            default:
            printf("Unknown TCP options \n");
            break;
        }

        i = i + length;
    }
}