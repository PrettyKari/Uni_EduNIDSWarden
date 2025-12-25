#include "parser.h"
#include <string.h>
#include <arpa/inet.h>

void parse_packet(size_t link_hdr_len, const u_char *packet,
                  const struct pcap_pkthdr *header,
                  struct packet_info *info)
{
    memset(info, 0, sizeof(*info));

    const u_char *ip_packet = packet + link_hdr_len;

    if (header->caplen < link_hdr_len + sizeof(struct iphdr)) {
        info->is_valid = 0;
        return;
    }

    const struct iphdr *iph = (const struct iphdr *)ip_packet;

    if (iph->version != 4) {
        info->is_valid = 0;
        return;
    }

    if (iph->protocol != IPPROTO_TCP) {
        info->is_valid = 0;
        return;
    }

    size_t ip_hdr_len = iph->ihl * 4;

    if (header->caplen < link_hdr_len + ip_hdr_len + sizeof(struct tcphdr)) {
        info->is_valid = 0;
        return;
    }

    const u_char *tcp_data = ip_packet + ip_hdr_len;
    const struct tcphdr *tcp = (const struct tcphdr *)tcp_data;

    info->src_ip    = iph->saddr;
    info->dst_ip    = iph->daddr;
    info->src_port  = ntohs(tcp->th_sport);
    info->dst_port  = ntohs(tcp->th_dport);
    info->protocol  = IPPROTO_TCP;

    // All checks passed
    info->is_valid = 1;
}