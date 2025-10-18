#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

int process_get_name(pid_t pid, char *name, size_t size);
int process_get_socket_inodes(pid_t pid, size_t *inodes, int max_inodes);

#endif // PROCESS_H