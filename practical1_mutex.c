#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define REPETITIONS 125000

int sharedValue = 0;
pthread_mutex_t lock;

void *unsafeIncrement(void *arg)
{
    for (int i = 0; i < REPETITIONS; i++)
    {
        sharedValue++;
    }
    return NULL;
}

void *safeIncrement(void *arg)
{
    for (int i = 0; i < REPETITIONS; i++)
    {
        pthread_mutex_lock(&lock);
        sharedValue++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t workers[NUM_THREADS];

    printf("=== Without Mutex ===\n");

    sharedValue = 0;

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&workers[i], NULL, unsafeIncrement, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(workers[i], NULL);

    printf("Final Counter: %d\n", sharedValue);

    printf("\n=== With Mutex ===\n");

    sharedValue = 0;
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&workers[i], NULL, safeIncrement, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(workers[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("Final Counter: %d\n", sharedValue);

    return 0;
}
