#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum) {        // Signal handler function
    printf("Received signal: %d\n", signum);
}

int main() {
    struct sigaction sa;
    sigset_t old_mask, new_mask;
    // Set up the signal handler
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    // Register signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Signal handler registered for SIGINT (Ctrl+C)\n");
    sigemptyset(&new_mask);        // Initialize new signal mask
    sigaddset(&new_mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, NULL, &old_mask) == -1) {     // Get current signal mask
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    // Check if SIGINT is already in the signal mask
    if (sigismember(&old_mask, SIGINT)) {
        printf("SIGINT is already present in the signal mask.\n");
    }
    else {
        // Add SIGINT to the signal mask
        if (sigprocmask(SIG_BLOCK, &new_mask, NULL) == -1)
        {
            perror("sigprocmask");
            exit(EXIT_FAILURE);
        }
        printf("Added SIGINT to the signal mask.\n");
    }
    while (1) {
        sleep(1);     // Wait for signals indefinitely
    }
    return 0;
}