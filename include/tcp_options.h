#ifndef TCP_OPTIONS_H
#define TCP_OPTIONS_H

#include <stdint.h>

void parse_tcp_options( const unsigned char *options, uint8_t options_length);

#endif
