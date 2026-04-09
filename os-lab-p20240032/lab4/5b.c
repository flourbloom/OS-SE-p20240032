#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    for (int i = 0; i < 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            /* Child process */
            printf("Child %d (PID %d): Sleeping 30 seconds...\n", i+1, getpid());
            sleep(30);
            printf("Child %d (PID %d): Exiting.\n", i+1, getpid());
            exit(0);
        }
    }

    /* Parent waits for all children */
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent: All children finished.\n");
    return 0;
}