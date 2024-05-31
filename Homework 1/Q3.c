#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    char names[n][100];
    for(int i=0;i<n;i++){
   //     fgets(names[i],100,stdin);
        scanf("%s",names[i]);
    }
    int m;
    scanf("%d",&m);
    char newNames[n+m][100];
    for(int i=0;i<n;i++){
        strcpy(newNames[i],names[i]);
    }
    char d[10]="delete";
    char s[10]="swap";
    char a[10]="add";
    for(int i=0;i<m;i++)
    {
        char command[10];
        scanf("%s",command);
        if(strcmp(command,d)==0){
            char name[100];
           // fgets(name,100,stdin);
            scanf("%s",name);
            int flag=0;
            for(int i=0;i<n;i++){
                if(strcmp(newNames[i],name)==0 && flag==0){
                    flag=1;
                }
                if(flag==1){
                    strcpy(newNames[i],newNames[i+1]);
                }
            }
            n--;
        }
        else if(strcmp(command,a)==0){
            char name[100];
            scanf("%s",name);
           // fgets(name,100,stdin);
            int place;
            scanf("%d",&place);
            char temp[100];
            for(int i=n;i>=place;i--){
                strcpy(newNames[i+1],newNames[i]);
            }
            strcpy(newNames[place],name);
            ++n;
        }
        else{
            char name1[100];
            char name2[100];
            int index1;
            int index2;
            scanf("%s",name1);
        //    fgets(name1,100,stdin);
          //  fgets(name2,100,stdin);
            scanf("%s",name2);
            for(int i=0;i<n;i++){
                if(strcmp(newNames[i],name1)==0){
                    index1=i;
                }
                if(strcmp(newNames[i],name2)==0){
                    index2=i;
                }
            }
            char temp[100];
            strcpy(temp,newNames[index1]);
            strcpy(newNames[index1],newNames[index2]);
            strcpy(newNames[index2],temp);
        }
    }
    for(int i=0;i<n-1;i++){
        printf("%s ",newNames[i]);
    }
    printf("%s",newNames[n-1]);
    return 0;
}