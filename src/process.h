#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

int process_get_name(pid_t pid, char *name, size_t size);
int process_get_socket_inodes(pid_t pid, size_t *inodes, int max_inodes);
void process_match_connections(connection_t *connections, int conn_count);

#endif // PROCESS_H