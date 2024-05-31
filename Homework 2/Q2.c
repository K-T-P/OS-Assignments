#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include<sys/wait.h>

int main()
{
    char words[100][100];
    int numberOfRepetition[500];
    for(int i=0;i<100;i++){
        numberOfRepetition[i]=0;
    }
    char validBeginnWord[7];
    int numberOfWords=0;
    scanf("%s", validBeginnWord);
    if (strcmp(validBeginnWord, "search") == 0)
    {
        char fileName[100];
        scanf("%s", fileName);
        for(int i=0;i<100;i++){
            scanf("%s",words[i]);
            if(strcmp(words[i],".")==0){
                break;
            }
            numberOfWords++;
        }
        for(int i=0;i<numberOfWords;i++){
            int temp=vfork();
            if(temp==0){
                FILE *openFile = fopen(fileName, "r");
                while(!feof(openFile)){
                    char filleWord[100];
                    fscanf(openFile,"%s",filleWord);
                    if(strcmp(filleWord,words[i])==0){
                        numberOfRepetition[i]++;
                    }
                    filleWord[0]='\0';
                }
                exit(0);
            }
        }
        for(int i=0;i<numberOfWords;i++){
            wait(NULL);
        }
        for(int i=0;i<numberOfWords;i++){
            printf("%s : %d\n",words[i],numberOfRepetition[i]);
        }
    }
    else
    {
        printf("Invalid operation!\n");
    }
    return 0;
}