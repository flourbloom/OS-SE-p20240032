/* (modified) zombie.c — Demonstrates a zombie process if need original find in https://github.com/RathpiseyAlpha/ITC-OS-2026/blob/main/labs/lab4/lab4-instruction.md#task-5--orphan--zombie-processes*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        /* Child */
        printf("Child (PID %d): Exiting immediately.\n", getpid());
        exit(0);
    }

    /* Parent */
    printf("Parent (PID %d): Child PID is %d.\n", getpid(), pid);
    printf("Parent: Sleeping 10 seconds before calling wait()...\n");
    sleep(10);

    printf("Parent: Calling wait() now to clean up zombie.\n");
    wait(NULL);

    printf("Parent: Child cleaned up. No zombie remains.\n");
    sleep(20);  // extra time to verify zombie is gone

    return 0;
}