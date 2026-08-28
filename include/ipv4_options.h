#ifndef IPV4_OPTIONS
#define IPV4_OPTIONS

#include <stdint.h>

void parse_ipv4_options ( const unsigned char *options, uint8_t options_length);

#endif