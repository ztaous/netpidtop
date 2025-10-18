#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

int process_get_name(pid_t pid, char *name, size_t size);
int process_count_sockets(pid_t pid);

#endif // PROCESS_H