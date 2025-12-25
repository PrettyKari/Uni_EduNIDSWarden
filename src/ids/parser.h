#ifndef PARSER_H
#define PARSER_H

#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

// Parsed fields for filtering
struct packet_info {
    uint32_t src_ip;    // network byte order
    uint32_t dst_ip;    // network byte order
    uint16_t src_port;  // host byte order
    uint16_t dst_port;  // host byte order
    uint8_t  protocol;  // IPPROTO_TCP or IPPROTO_UDP
    int is_valid;  		// err flag
};

/* Parse Ethernet IPv4 to TCP/UDP headers
 * Sets info is_valid = 0 as flag on error or non-matching protocol. */
void parse_packet(const u_char *packet, const struct pcap_pkthdr *header, struct packet_info *info);

#endif /* PARSER_H */