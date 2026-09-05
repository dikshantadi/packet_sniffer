#ifndef CAPTURE_H
#define CAPTURE_H

#include "stat.h"

void list_interfaces(void);
void open_capture(const char *device, struct capture_stats *stats);

#endif
