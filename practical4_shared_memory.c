#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main()
{
    key_t key;
    int shmid;
    char *memory;

    key = ftok(".", 90);

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid < 0)
    {
        printf("Unable to create shared memory.\n");
        return 1;
    }

    memory = (char *)shmat(shmid, NULL, 0);

    if (memory == (char *)-1)
    {
        printf("Unable to attach shared memory.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed.\n");
        return 1;
    }

    if (pid == 0)
    {
        sleep(1);

        printf("\nChild Process\n");
        printf("Received Message: %s\n", memory);

        shmdt(memory);
    }
    else
    {
        strcpy(memory, "Operating Systems Practical - Shared Memory Communication");

        printf("Parent Process\n");
        printf("Message Written Successfully.\n");

        wait(NULL);

        shmdt(memory);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
