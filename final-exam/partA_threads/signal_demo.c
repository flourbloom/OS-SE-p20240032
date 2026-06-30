#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void cleanup(int sig)
{
    if(sig==SIGINT)
        printf("\nCaught SIGINT\n");

    if(sig==SIGTERM)
        printf("\nCaught SIGTERM\n");

    printf("Cleaning up...\n");
    exit(0);
}

int main()
{
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    while(1)
    {
        printf("Program running... PID=%d\n", getpid());
        sleep(2);
    }

    return 0;
}
