#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"
#include "process.h"
#include "network.h"
#include "ui.h"

static int running = 1;

int main(void)
{
    ui_init();

    while (running) {
        connection_t *connections;
        int count;

        if (network_get_connections(&connections, &count) < 0) {
            printf("Failed to read connections\n");
            return 1;
        }

        process_match_connections(connections, count);
        ui_display_connections(connections, count);
        free(connections);

        if (ui_handle_input()) {
            break;
        }

        usleep(500000);
    }

    ui_cleanup();
    return 0;
}