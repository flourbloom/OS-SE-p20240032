#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *worker(void *arg)
{
    long id = (long)arg;

    int *result = malloc(sizeof(int));
    *result = (id + 1) * 25;

    printf("Worker %ld running (thread id %lu), computed value = %d\n",
           id,
           pthread_self(),
           *result);

    sleep(2); // shortened so exam demo is practical

    pthread_exit(result);
}

int main()
{
    pthread_t threads[NUM_THREADS];

    // Create initial threads
    for (long i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, worker, (void *)i);
    }

    int total = 0;

    // Join threads and collect results
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int *value;

        pthread_join(threads[i], (void **)&value);

        printf("Joined worker %d -> %d\n", i, *value);

        total += *value;

        free(value);
    }

    printf("\nSummary\n");
    printf("Workers : %d\n", NUM_THREADS);
    printf("Total   : %d\n", total);

    // ============================
    // CURVEBALL (Part A requirement)
    // spawn AFTER join completes
    // ============================

    printf("\n--- Curveball: spawning extra worker AFTER join ---\n");

    pthread_t extra;
    int *extra_value;

    pthread_create(&extra, NULL, worker, (void *)99);
    pthread_join(extra, (void **)&extra_value);

    printf("Extra worker joined -> %d\n", *extra_value);

    free(extra_value);

    return 0;
}
