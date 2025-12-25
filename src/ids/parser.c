#include "parser.h"
#include <netinet/tcp.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void parse_packet(size_t link_hdr_len, const u_char *packet,
                  const struct pcap_pkthdr *header,
                  struct packet_info *info)
{
    (void)header;  // unused

    memset(info, 0, sizeof(*info));

    // IP header starts after Ethernet
    const u_char *ip_packet = packet + link_hdr_len;
    if (header->caplen < link_hdr_len + sizeof(struct iphdr)) {
        info->is_valid = 0;
        return;
    }
    struct iphdr *iph = (struct iphdr *)ip_packet;


	if (iph->version != 4) {
    info->is_valid = 0;
    return;
	}
	if (iph->protocol != IPPROTO_TCP) {
    info->is_valid = 0;
    return;
	}

    size_t ip_hdr_len = iph->ihl * 4;
	const u_char *tp = ip_packet + ip_hdr_len;
	if (header->caplen < link_hdr_len + ip_hdr_len + sizeof(struct tcphdr)) {
		info->is_valid = 0;
		return;
	}

    info->src_ip = iph->saddr;
    info->dst_ip = iph->daddr;
    info->protocol = iph->protocol;

    // Transport header
	const struct tcphdr *tcp = (const struct tcphdr *)tp;
	info->src_port = ntohs(tcp->th_sport);   // source port
	info->dst_port = ntohs(tcp->th_dport);   // destination port

    info->is_valid = 1;
}