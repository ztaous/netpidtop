#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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

    // ajouter initialisation de systèmes

    while (running) {
        printf("main loop running\n");
        sleep(1);
    }

    // ajouter du cleanup plus tard

    return 0;
}