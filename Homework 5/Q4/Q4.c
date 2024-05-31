#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMBER_OF_RESOURCES 5
#define NUMBER_OF_THREADS 10

typedef struct
{
    int resources[NUMBER_OF_RESOURCES];
    sem_t availableResources;
    pthread_mutex_t poolMutex;
} ResourceManager;
ResourceManager RM;

void *ThreadFunc(void *args)
{
    int ThreadNumber = (int)args;
    int resourceNum = -1;
    int taskNum = rand() % 20 + 1;
    for (int i = 0; i < taskNum; i++)
    {
        sem_wait(&RM.availableResources);
        pthread_mutex_lock(&RM.poolMutex);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            if (RM.resources[j] == -1)
            {
                RM.resources[j] = ThreadNumber;
                resourceNum = j;
                break;
            }
        }
        pthread_mutex_unlock(&RM.poolMutex);
        if (RM.resources[resourceNum] != ThreadNumber)
        {
            resourceNum = -1;
            i--;
            continue;
        }
        printf("Thread %d is performing work with resource %d\n", ThreadNumber, resourceNum + 1);
        sleep(rand() % 20 + 1);
        RM.resources[resourceNum] = -1;
        resourceNum = -1;
        sem_post(&RM.availableResources);
    }
}

int main()
{
    sem_init(&RM.availableResources, 0, 5);
    pthread_mutex_init(&RM.poolMutex, NULL);
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        RM.resources[i] = -1;
    }
    pthread_t threads[10];
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, ThreadFunc, (void *)i);
    }
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&RM.poolMutex);
    sem_close(&RM.availableResources);
}