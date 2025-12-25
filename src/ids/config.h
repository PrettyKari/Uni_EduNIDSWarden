#ifndef CONFIG_H
#define CONFIG_H

// Network interface for packet capture, "lo" for loopback
#define INTERFACE "lo"

// Destination ports (must match server)
#define ALLOWED_PORTS {5050U, 8060U, 3020U}
#define ALLOWED_PORTS_COUNT 3U

// IP: 127.0.0.1 in network byte order
#define ALLOWED_SOURCE_IP 0x7F000001U

// Log file paths (executable directory location).
#define LOG_ALL_TRAFFIC    "../logs/all_traffic.log"
#define LOG_SUSPICIOUS     "../logs/suspicious.log"

// Enable (1) or disable (0) logging of all packets
#define VERBOSE_LOGGING 1

#endif /* CONFIG_H */