#include "parser.h"
#include <string.h>
#include <net/ethernet.h>
#include <netinet/in.h>

void parse_packet(const u_char *packet, const struct pcap_pkthdr *header,
                  struct packet_info *info)
{
    (void)header;  // unused

    memset(info, 0, sizeof(*info));

    // Ethernet header: 14 bytes
    if (header->caplen < 14) {
        info->is_valid = 0;
        return;
    }
    struct ether_header *eth = (struct ether_header *)packet;
    if (ntohs(eth->ether_type) != ETHERTYPE_IP) {
        info->is_valid = 0;
        return;
    }

    // IP header starts after Ethernet
    const u_char *ip_packet = packet + 14;
    if (header->caplen < 14 + sizeof(struct iphdr)) {
        info->is_valid = 0;
        return;
    }
    struct iphdr *iph = (struct iphdr *)ip_packet;

    if (iph->version != 4 || iph->protocol != IPPROTO_TCP && iph->protocol != IPPROTO_UDP) {
        info->is_valid = 0;
        return;
    }

    size_t ip_hdr_len = iph->ihl * 4;
    if (header->caplen < 14 + ip_hdr_len + 4) {
        info->is_valid = 0;
        return;
    }

    info->src_ip = iph->saddr;
    info->dst_ip = iph->daddr;
    info->protocol = iph->protocol;

    // Transport header
    const u_char *trans = ip_packet + ip_hdr_len;
    info->src_port = ntohs(((uint16_t *)trans)[0]);
    info->dst_port = ntohs(((uint16_t *)trans)[1]);

    info->is_valid = 1;
}