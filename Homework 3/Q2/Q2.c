#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

// semaphore declarations
sem_t sem;

void* p1(void* arg){
    sem_t*sem = (sem_t*)arg;
    char array[] = {'F','E','G'};
    for(int i=0;i<3;i++){
        sem_wait(sem);
        printf("%c\n",array[i]);
        sem_post(sem);
    }
}

void* p2(void* arg){
    sem_t*sem = (sem_t*)arg;
    char array[] = {'A','C','B'};
    for(int i=0;i<3;i++){
        sem_post(sem);
        printf("%c\n",array[i]);
        sem_wait(sem);
    }
}



int main(){
    // semaphore initializations
    char * sem_name = "semaphore";
    sem_init(&sem,0,0);
    //sem_open(sem_name,O_CREAT,0666,2);
    // thread creations
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1,NULL,p1,(void*)&sem);
    pthread_create(&t2,NULL,p2,(void*)&sem);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_close(&sem);
    return 0;
}