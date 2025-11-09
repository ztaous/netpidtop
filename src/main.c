#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"
#include "process.h"
#include "network.h"

static int running = 1;

void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        running = 0;
    }
}

int main(void) {
    // ajout possible de root checking

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    connection_t *connections;
    int count;

    // while (running) {
    //     printf("main loop running\n");
    //     sleep(10);
    // }

    if (network_get_connections(&connections, &count) < 0) {
        printf("Failed to read /proc/net/tcp\n");
        return 1;
    }

    process_match_connections(connections, count);

    printf("%-20s %-8s %-21s %-21s %-12s\n",
        "Process", "PID", "Local", "Remote", "State");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if(connections[i].owner_pid > 0) {
            print_connection(&connections[i]);
        }
    }
    free(connections);
    printf("\n");
    
    return 0;
}