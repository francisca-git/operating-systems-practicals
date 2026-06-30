#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define ITEMS 10

int queue[SIZE];
int front = 0;
int rear = 0;

sem_t emptySlots;
sem_t filledSlots;
sem_t bufferLock;

void displayBuffer()
{
    printf("Buffer: [");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d", queue[i]);
        if (i < SIZE - 1)
            printf(" ");
    }
    printf("]\n");
}

void *producer(void *arg)
{
    for (int item = 1; item <= ITEMS; item++)
    {
        sem_wait(&emptySlots);
        sem_wait(&bufferLock);

        queue[rear] = item;
        printf("Producer added %d\n", item);

        rear = (rear + 1) % SIZE;

        displayBuffer();

        sem_post(&bufferLock);
        sem_post(&filledSlots);

        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg)
{
    int value;

    for (int i = 0; i < ITEMS; i++)
    {
        sem_wait(&filledSlots);
        sem_wait(&bufferLock);

        value = queue[front];
        queue[front] = 0;

        printf("Consumer removed %d\n", value);

        front = (front + 1) % SIZE;

        displayBuffer();

        sem_post(&bufferLock);
        sem_post(&emptySlots);

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t producerThread;
    pthread_t consumerThread;

    sem_init(&emptySlots, 0, SIZE);
    sem_init(&filledSlots, 0, 0);
    sem_init(&bufferLock, 0, 1);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);
    sem_destroy(&bufferLock);

    return 0;
}
