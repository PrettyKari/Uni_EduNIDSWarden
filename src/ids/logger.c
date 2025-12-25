#include "logger.h"
#include "utils.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *all_fp = NULL;
static FILE *susp_fp = NULL;

int logger_init(void)
{
    all_fp = fopen(LOG_ALL_TRAFFIC, "a");
    if (!all_fp) {
        return -1;
    }
    susp_fp = fopen(LOG_SUSPICIOUS, "a");
    if (!susp_fp) {
        fclose(all_fp);
        return -1;
    }
    return 0;
}

void logger_cleanup(void)
{
    if (all_fp) {
        fclose(all_fp);
        all_fp = NULL;
    }
    if (susp_fp) {
        fclose(susp_fp);
        susp_fp = NULL;
    }
}

void log_packet(const struct packet_info *info, int suspicious)
{
    if (!info->is_valid) {
        return;
    }

    char ts[20];
    char src_ip[16], dst_ip[16];
    char src_port[6], dst_port[6];
    timestamp_str(ts);
    ip_ntoa(info->src_ip, src_ip);
    ip_ntoa(info->dst_ip, dst_ip);
    port_ntoa(info->src_port, src_port);
    port_ntoa(info->dst_port, dst_port);

    const char *proto = (info->protocol == IPPROTO_TCP) ? "TCP" : "UDP";

    char line[256];
    snprintf(line, sizeof(line), "[%s] %s:%s -> %s:%s %s%s",
             ts, src_ip, src_port, dst_ip, dst_port, proto,
             suspicious ? " (SUSPICIOUS)" : "");

    // Write to all_traffic.log if verbose or suspicious
    if (VERBOSE_LOGGING || suspicious) {
        if (all_fp) {
            fprintf(all_fp, "%s\n", line);
            fflush(all_fp);
        }
    }

    // Always write to suspicious.log if flagged
    if (suspicious && susp_fp) {
        fprintf(susp_fp, "%s\n", line);
        fflush(susp_fp);
    }
}