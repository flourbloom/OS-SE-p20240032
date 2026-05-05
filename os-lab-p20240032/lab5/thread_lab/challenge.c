#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

// Global flag to control thread execution
volatile sig_atomic_t keep_running = 1;

// Signal handler
void handle_sigint(int sig) {
    printf("\n[Signal] SIGINT received. Stopping threads...\n");
    keep_running = 0;
}

// Worker thread function
void* worker(void* arg) {
    long tid = (long)arg;

    while (keep_running) {
        printf("Worker thread %ld is running...\n", tid);
        sleep(1);
    }

    printf("Worker thread %ld exiting gracefully.\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    // Register signal handler
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Failed to register SIGINT handler");
        return 1;
    }

    printf("Main thread PID: %d\n", getpid());
    printf("Press Ctrl+C to stop...\n");

    // Create threads
    pthread_create(&t1, NULL, worker, (void*)1);
    pthread_create(&t2, NULL, worker, (void*)2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");
    return 0;
}