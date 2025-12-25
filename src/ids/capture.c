#include "parser.h"
#include "capture.h"
#include "filter.h"
#include "logger.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

static void packet_handler(u_char *link_hdr_len_ptr, const struct pcap_pkthdr *h, const u_char *packet)
{
	size_t link_hdr_len = *(size_t *)link_hdr_len_ptr;

	struct packet_info info;
	parse_packet(link_hdr_len, packet, h, &info);

	int suspicious = is_suspicious(&info);
	log_packet(&info, suspicious);
	}

int start_capture(void)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(INTERFACE, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "pcap_open_live failed: %s\n", errbuf);
        return -1;
    }

//	int dlt = pcap_datalink(handle);
	size_t link_hdr_len = 4;
/*
*	if (dlt == DLT_EN10MB) {
*		link_hdr_len = 14;  / Ethernet header /
*	} else if (dlt == DLT_NULL || dlt == DLT_LOOP) {
*		link_hdr_len = 4;   / Loopback pseudo-header /
*	} else {
*		fprintf(stderr, "Unsupported datalink type: %d\n", dlt);
*		pcap_close(handle);
*		return -1;
*	} */

	// Store link_hdr_len for use in parser

    printf("Capturing on interface %s...\n", INTERFACE);

    pcap_loop(handle, 0, packet_handler, (u_char *)&link_hdr_len);

    pcap_close(handle);
    return 0;  // only reached on error or break
}