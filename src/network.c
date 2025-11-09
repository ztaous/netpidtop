#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int network_get_connections(connection_t **connections, int *count) {
    FILE *f = fopen("/proc/net/tcp", "r");
    if (!f) return -1;
    
    char line[512];
    // on skip la première ligne (headers), si ça échoue on ferme
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return -1;
    }
    
    size_t capacity = 64;
    size_t len = 0;
    connection_t *arr = malloc(capacity * sizeof(*arr));
    if (!arr) {
        fclose(f);
        return -1;
    }
    
    while (fgets(line, sizeof(line), f)) {
        unsigned int local_addr, local_port;
        unsigned int remote_addr, remote_port;
        unsigned int state;
        unsigned long long inode; // large pour éviter overflow (cast plus tard)
        
        // on parse les lignes dans le fichier /proc/net/tcp
        int matches = sscanf(line,
            " %*d: %08X:%04X %08X:%04X %02X %*08X:%*08X %*02X:%*08X %*08X %*u %*d %llu",
            &local_addr, &local_port,
            &remote_addr, &remote_port,
            &state, &inode);
            
        if (matches != 6) continue;
        
        // si la limite est atteinte, on fait de la réallocation
        if (len == capacity) {
            capacity *= 2;
            connection_t *tmp = realloc(arr, capacity * sizeof(*tmp));
            if (!tmp) {
                free(arr);
                fclose(f);
                return -1;
            }
            arr = tmp;
        }
        
        arr[len].local_addr = local_addr;
        arr[len].local_port = local_port;
        arr[len].remote_addr = remote_addr;
        arr[len].remote_port = remote_port;
        arr[len].state = state;
        arr[len].inode = (uint32_t)inode;
        arr[len].owner_pid = -1;
        len++;
    }
    
    fclose(f);
    *connections = arr;
    *count = len;
    return 0;
}