
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int index[n];
    int age[n];
    int point[n];
    char names[n][100];
    int lowestPointIndex=0;
    int lowestPoint=0;
    for(int i=0;i<n;i++){
        scanf("%s",names[i]);
        scanf("%d",&age[i]);
        scanf("%d",&point[i]);
        if(i==0){
            lowestPointIndex=0;
            lowestPoint=point[0];}
        else{
            if(point[i]<lowestPoint){
                lowestPoint=point[i];
                lowestPointIndex=i;}
        }
    }
    if(n%2==1){
        for(int i=lowestPointIndex;i<n;i++){
            age[i]=age[i+1];
            point[i]=point[i+1];
            index[i]=index[i+1];
            strcpy(names[i],names[i+1]);
        }
        n--;
    }
    char newNames[n][100];
    int z=0;
    for(int i=0;i<n;i++){
        if(i==lowestPointIndex){
            z=1;
            continue;
        }
        strcpy(newNames[i],names[i+1]);
    }
    int sortedPoints[n/2];
    int sortedIndexes[n/2];
    for(int i=0;i<n/2;i++){
        sortedPoints[i]=point[i]+point[n-i-1];
        sortedIndexes[i]=i;
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n/2-1;j++){
            if(sortedPoints[j]<sortedPoints[j+1]){
                int temp=sortedPoints[j];
                sortedPoints[j]=sortedPoints[j+1];
                sortedPoints[j+1]=temp;
                
                int tempIndex=sortedIndexes[j];
                sortedIndexes[j]=sortedIndexes[j+1];
                sortedIndexes[j+1]=tempIndex;
            }
        }
    }
    
    for(int i=0;i<n/2;i++){
        printf("%s %d %d, %s %d %d\n",names[sortedIndexes[i]],age[sortedIndexes[i]],
        point[sortedIndexes[i]],names[n-1-sortedIndexes[i]],age[n-1-sortedIndexes[i]],point[n-1-sortedIndexes[i]]);
    }
    return 0;
}