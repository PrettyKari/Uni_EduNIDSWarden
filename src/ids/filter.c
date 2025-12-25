#include "filter.h"
#include <stdint.h>

static const uint16_t allowed_ports[] = ALLOWED_PORTS;

int port_is_allowed(uint16_t port)
{
    uint16_t host_port = ntohs(port);
    for (size_t i = 0; i < ALLOWED_PORTS_COUNT; ++i) {
        if (host_port == allowed_ports[i]) {
            return 1;
        }
    }
    return 0;
}

int is_suspicious(const struct packet_info *info)
{
    if (!info->is_valid) {
        return 0;  // ignore invalid packets
    }

    // Rule 1: source IP must be 127.0.0.1
    if (info->src_ip != ALLOWED_SOURCE_IP) {
        return 1;
    }

    // Rule 2: destination port must be in allowed list
    if (!port_is_allowed(info->dst_port)) {
        return 1;
    }

    return 0;
}