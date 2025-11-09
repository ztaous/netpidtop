#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>

#define MAX_PROCESS_NAME 256
#define MAX_SOCKETS_PER_PROCESS 64

typedef struct {
    uint32_t inode;
    uint32_t local_addr;
    uint16_t local_port;
    uint32_t remote_addr;
    uint16_t remote_port;
    uint8_t state;
    pid_t owner_pid;
} connection_t;

typedef struct {
    pid_t pid;
    char name[MAX_PROCESS_NAME];
    int socket_count;
    uint32_t inodes[MAX_SOCKETS_PER_PROCESS];
} process_info_t;

int is_number(const char *str);

#endif // COMMON_H