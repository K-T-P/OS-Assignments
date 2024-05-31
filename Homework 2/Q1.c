#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>


typedef struct
{
    char path[500];
    char fileName[100];
} Info;

void *ThreadFunc(void *args)
{
    Info dirInfo = *(Info *)args;
    DIR *dir = opendir(dirInfo.path);
    if (dir == NULL)
    {
        // Some folders are system folders and cannot
        // be accessed and their dir beomes NULL.
        // This is the reason that this condition exists.
        // "DO NOTHING" CONDITION
    }
    else
    {
        struct dirent *entry;
        pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t) * 500);
        int threadSize = 500;
        Info *pp = (Info *)malloc(sizeof(Info) * 500);
        int num = -1;
        char*searchedEntries[500];

        while ((entry = readdir(dir)) != NULL)
        {
            // 4 equals to DT_DIR
            // sometimes compiler does not recognize DT_DIR
            if (entry->d_type == 4)
            {
                char lastChar = (entry->d_name)[strlen(entry->d_name) - 1];

                // skips .. and .
                if (lastChar == '.')
                    continue;
                num++;
                if (num == threadSize)
                {
                    threadSize += 500;
                    thread = (pthread_t *)realloc(thread, sizeof(pthread_t) * threadSize);
                }
                int oldPathStringLength = sizeof(dirInfo.path) / sizeof(char);
                int newEntryStringLength = sizeof(entry->d_name) / sizeof(char);
                char *newPath = (char *)malloc(sizeof(char) * (oldPathStringLength + newEntryStringLength));
                newPath[0] = '\0';

                strcat(newPath, dirInfo.path);
                strcat(newPath, "/");
                strcat(newPath, entry->d_name);

                strcpy((pp->path), newPath);
                strcpy(pp->fileName, dirInfo.fileName);
                searchedEntries[num]=(char*)malloc(sizeof(char*)*500);
                strcpy(searchedEntries[num],newPath);

                for(int i=0;i<=num;i++){
                    if(strcmp(searchedEntries[i],newPath)==0){
                        continue;
                    }
                }
                free(newPath);
                pthread_create(&thread[num], NULL, ThreadFunc, pp);
            }
            else
            {
                if (strcmp(entry->d_name, dirInfo.fileName) == 0)
                {
                    printf("[+] FOUND:\n%s/%s\n", dirInfo.path, dirInfo.fileName);
                }
            }
        }
        for (int i = 0; i <= num; i++)
        {
            pthread_join(thread[i], NULL);
        }
        free(thread);
        free(pp);
    }
    closedir(dir);
    return NULL;
}

int main()
{
    char search[7];
    char startDir[500];
    char fileName[100];
    Info *inf = (Info *)malloc(sizeof(Info));
    scanf("%s", search);
    scanf("%s", startDir);
    scanf("%s", fileName);
    if (strcmp(search, "search") == 0)
    {
        strcpy(inf->path, startDir);
        strcpy(inf->fileName, fileName);
        pthread_t thread;
        pthread_create(&thread, NULL, ThreadFunc, inf);
        pthread_join(thread, NULL);
    }
    else
    {
        printf("Invalid command!\n");
    }
    free(inf);
    return 0;
}