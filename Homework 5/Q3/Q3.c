#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define BUFFER_SIZE 40

char buffer[BUFFER_SIZE];
int head = 0;
int tail = 0;
pthread_t threadID[2];
pthread_mutex_t lock;

void* ReadFile(void * args){
    char * source_file_path = (char*)args;
    FILE * fptr;
    fptr = fopen(source_file_path,"r");
    char c;
    bool flag = true;
    while (flag){
        c = getc(fptr);
        if(c==EOF){
            flag = false;
        }
        while((head +1)%BUFFER_SIZE == tail);
        pthread_mutex_lock(&lock);
        buffer[head] = c;
        head = (head +1)%BUFFER_SIZE;
        pthread_mutex_unlock(&lock);
    }
    fclose(fptr);
}
void* WriteFile(void * args){
    char * destination_file_path = (char*)args;
    FILE * fptr;
    fptr = fopen(destination_file_path,"w");
    char c ;
    while (true){
        while(head == tail);
        pthread_mutex_lock(&lock);
        c = buffer[tail];
        tail = (tail+1)%BUFFER_SIZE ;
        pthread_mutex_unlock(&lock);
        if(c==EOF)
            break;
        fputc(c,fptr);
    }
    fclose(fptr);
}

int main(int argc, char **argv){
    char * source_file_path = argv[1];
    char * destination_file_path = argv[2];
    pthread_mutex_init(&lock,NULL);
    pthread_create(&threadID[0],NULL,ReadFile,(void*)source_file_path);
    pthread_create(&threadID[1],NULL,WriteFile,(void*)destination_file_path);
    pthread_join(threadID[0],NULL);
    pthread_join(threadID[1],NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}