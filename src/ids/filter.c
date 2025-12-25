#include "filter.h"
#include <stdint.h>


int port_is_allowed(uint16_t port)
{
    uint16_t host_port = ntohs(port);
    static const uint16_t allowed_ports[] = { 5050U, 8060U, 3020U };
	static const size_t allowed_ports_count = 3;
    for (size_t i = 0; i < allowed_ports_count; ++i) {
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