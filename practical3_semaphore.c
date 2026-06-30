#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 5
#define ITERATIONS 100000

int total = 0;
sem_t access;

void *updateCounter(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        sem_wait(&access);

        total++;

        sem_post(&access);
    }

    return NULL;
}

int main()
{
    pthread_t thread[THREAD_COUNT];

    /* Binary semaphore */
    sem_init(&access, 0, 1);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&thread[i], NULL, updateCounter, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(thread[i], NULL);
    }

    printf("Shared Counter = %d\n", total);

    printf("\nObservations\n");
    printf("1. Binary semaphore allows only one thread into the critical section.\n");
    printf("2. Mutex is designed specifically for mutual exclusion.\n");
    printf("3. A counting semaphore (e.g., value = 3) can permit up to three threads simultaneously.\n");

    sem_destroy(&access);

    return 0;
}
