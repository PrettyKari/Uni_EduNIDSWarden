#ifndef FILTER_H
#define FILTER_H

#include "parser.h"
#include "config.h"

// Return 1 if packet violates rules (suspicious)
int is_suspicious(const struct packet_info *info);

// Return 1 if destination port is ALLOWED_PORTS
int port_is_allowed(uint16_t port);

#endif /* FILTER_H */