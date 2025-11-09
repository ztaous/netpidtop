#include "process.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int process_get_name(pid_t pid, char *name, size_t size)
{
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);

    FILE *file = fopen(path, "r");
    if (!file) {
        return -1;
    }

    if(!fgets(name, size, file)) {
        fclose(file);
        return -1;
    }

    size_t len = strlen(name);
    if (len > 0 && name[len-1] == '\n') {
        name[len-1] = '\0';
    }

    fclose(file);
    return 0;
}

int process_get_socket_inodes(pid_t pid, uint32_t **inodes, int *count)
{
    *inodes = NULL;
    *count = 0;
    
    char fd_path[256];
    snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd", pid);

    DIR *fd_dir = opendir(fd_path);
    if (!fd_dir) {
        return -1;
    }

    int socket_count = 0;
    size_t cap = 16;
    uint32_t *buf = malloc(cap * sizeof *buf);
    if (!buf) { 
        closedir(fd_dir); 
        return -1; 
    }

    struct dirent *entry;

    while ((entry = readdir(fd_dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char link_path[512];
        snprintf(link_path, sizeof(link_path), "%s/%s", fd_path, entry->d_name);

        char link_target[256];
        ssize_t len = readlink(link_path, link_target, sizeof(link_target) - 1);

        if (len > 0) {
            link_target[len] = '\0';

            uint32_t inode;
            if (sscanf(link_target, "socket:[%u]", &inode) == 1) {
                if ((size_t)socket_count == cap) {
                    cap *= 2;
                    uint32_t *tmp = realloc(buf, cap * sizeof *tmp);
                    if (!tmp) { free(buf); closedir(fd_dir); return -1; }
                    buf = tmp;
                }
                buf[socket_count++] = inode;
            }
        }
    }

    closedir(fd_dir);
    *inodes = buf;
    *count = socket_count;
    return 0;
}

void process_match_connections(connection_t *connections, int conn_count)
{
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        if (!is_number(entry->d_name)) continue;

        pid_t pid = atoi(entry->d_name);
        uint32_t *inodes;
        int inode_count;

        if (process_get_socket_inodes(pid, &inodes, &inode_count) < 0) continue;

        for (int i = 0; i < inode_count; i++) {
            for (int j = 0; j < conn_count; j++) {
                if (connections[j].inode == inodes[i]) {
                    connections[j].owner_pid = pid;
                }
            }
        }
        free(inodes);
    }
    closedir(proc_dir);
}
