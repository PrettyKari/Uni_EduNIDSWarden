#include "logger.h"
#include "capture.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static void signal_handler(int sig)
{
    (void)sig;
    logger_cleanup();
    exit(0);
}

int main(void)
{
    if (logger_init() != 0) {
        fprintf(stderr, "Failed to open log files\n");
        return 1;
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (start_capture() != 0) {
        logger_cleanup();
        return 1;
    }

    logger_cleanup();
    return 0;
}