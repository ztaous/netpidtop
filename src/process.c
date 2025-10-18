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

int process_count_sockets(pid_t pid)
{
    char fd_path[256];
    snprintf(fd_path, sizeof(fd_path),  "/proc/%d/fd", pid);

    DIR *fd_dir = opendir(fd_path);
    if (!fd_dir) {
        return -1;
    }

    int socket_count = 0;
    struct dirent *entry;

    while ((entry = readdir(fd_dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char link_path[512];
        snprintf(link_path, sizeof(link_path), "%s/%s", fd_path, entry->d_name);

        char target[256];
        ssize_t len = readlink(link_path, target, sizeof(target) - 1);

        if (len > 0) {
            target[len] = '\0';

            if (strncmp(target, "socket:[", 8) == 0) {
                socket_count++;
            }
        }
    }

    closedir(fd_dir);
    return socket_count;
}
