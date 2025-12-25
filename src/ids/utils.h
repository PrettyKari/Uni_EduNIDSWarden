#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

/* Convert network byte order IPv4 address to dotted decimal string.
 * buf must be at least 16 bytes. Returns buf. */
char *ip_ntoa(uint32_t addr, char buf[16]);

/* Convert network byte order port to decimal string.
 * buf must be at least 6 bytes. Returns buf. */
char *port_ntoa(uint16_t port, char buf[6]);

/* Format current time as "YYYY-MM-DD HH:MM:SS".
 * buf must be at least 20 bytes. Returns buf. */
char *timestamp_str(char buf[20]);

#endif /* UTILS_H */