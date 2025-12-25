#include "utils.h"
#include <arpa/inet.h>
#include <stdio.h>

char *ip_ntoa(uint32_t addr, char buf[16])
{
    uint32_t host_addr = ntohl(addr);
    snprintf(buf, 16, "%u.%u.%u.%u",
             (host_addr >> 24) & 0xFF,
             (host_addr >> 16) & 0xFF,
             (host_addr >> 8)  & 0xFF,
             host_addr         & 0xFF);
    return buf;
}

char *port_ntoa(uint16_t port, char buf[6])
{
    uint16_t host_port = ntohs(port);
    snprintf(buf, 6, "%u", host_port);
    return buf;
}

char *timestamp_str(char buf[20])
{
    time_t now = time(NULL);
    struct tm tm_info;
    localtime_r(&now, &tm_info);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", &tm_info);
    return buf;
}