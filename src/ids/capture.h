#ifndef CAPTURE_H
#define CAPTURE_H

/* Start pcap loop on INTERFACE
 * Blocks until error or interrupt
 * Returns -1 on init failure, otherwise does not return. */
int start_capture(void);

#endif /* CAPTURE_H */