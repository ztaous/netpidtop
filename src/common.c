#include "common.h"
#include "process.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int is_number(const char *str)
{
	while (*str) {
		if (*str < '0' || *str > '9')
			return 0;
		str++;
	}
	return 1;
}

void addr_to_string(uint32_t addr, uint16_t port, char *buf, size_t size)
{
	struct in_addr in;

	// inverse les bytes
	// (hostlong -> network byte order)
	// (little-endian -> big-endian)
	in.s_addr = htonl(addr);

	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &in, ip_str,
		  sizeof(ip_str)); // conversion au format "127.0.0.1"

	snprintf(buf, size, "%s:%d", ip_str, port);
}

const char *state_to_string(uint8_t state)
{
	// convertir hex states vers string
	// enum dans linux/include/net.tcp_states.h (kernel)
	switch (state) {
	case 0X01:
		return "TCP_ESTABLISHED";
	case 0x0A:
		return "TCP_LISTEN";
	case 0x06:
		return "TCP_TIME_WAIT";
	case 0x08:
		return "CLOSE_WAIT";
	default:
		return "OTHER";
	}
}

void print_connection(connection_t *conn)
{
	char proc_name[256];
	if (process_get_name(conn->owner_pid, proc_name, sizeof(proc_name)) <
	    0) {
		strcpy(proc_name, "unknown");
	}

	char local[32];
	addr_to_string(conn->local_addr, conn->local_port, local,
		       sizeof(local));

	char remote[32];
	addr_to_string(conn->remote_addr, conn->remote_port, remote,
		       sizeof(remote));

	printf("%-20s %-8d %-21s %-21s %-12s\n", proc_name, conn->owner_pid,
	       local, remote, state_to_string(conn->state));
}