#ifndef LOGGER_H
#define LOGGER_H

#include "parser.h"
#include <stdio.h>

// Open both log files. Call once at start. Returns 0 on success, -1
int logger_init(void);

// Close both log files. Call at exit.
void logger_cleanup(void);

/* Log packet according to rules and logging mode
 * Writes to all_traffic.log depending on logging mode
 * Always writes to suspicious.log if suspicious == 1. */
void log_packet(const struct packet_info *info, int suspicious);

#endif /* LOGGER_H */