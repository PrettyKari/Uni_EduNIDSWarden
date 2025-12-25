#include "capture.h"
#include "parser.h"
#include "filter.h"
#include "logger.h"
#include "config.h"
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

static void packet_handler(u_char *user, const struct pcap_pkthdr *header,
                           const u_char *packet)
{
    (void)user;  // unused

    struct packet_info info;
    parse_packet(packet, header, &info);

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

    if (pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr, "Interface %s is not Ethernet\n", INTERFACE);
        pcap_close(handle);
        return -1;
    }

    printf("Capturing on interface %s...\n", INTERFACE);

    pcap_loop(handle, 0, packet_handler, NULL);

    pcap_close(handle);
    return 0;  // only reached on error or break
}